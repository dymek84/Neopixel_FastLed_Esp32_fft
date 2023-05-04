
#pragma once

#include "Imports.h"
#define I2S_WS 25
#define I2S_SD 33
#define I2S_SCK 32
#define bufferLen 16
int32_t sBuffer[bufferLen];
#define I2S_PORT I2S_NUM_0
const int numBands = 16;
void i2s_install()
{

    const i2s_config_t i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive, not transfer
        .sample_rate = 16000,                              // 16KHz 44100
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,      // could only get it to work with 32bits
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,      // although the SEL config should be left, it seems to transmit on right
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Interrupt level 1
        .dma_buf_count = 2,                       // number of buffers
        .dma_buf_len = bufferLen                  // samples per buffer
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin()
{
    // Set I2S pin configuration
    const i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,
        .ws_io_num = I2S_WS,
        .data_out_num = -1,
        .data_in_num = I2S_SD};

    i2s_set_pin(I2S_PORT, &pin_config);
}

void setup_i2s()
{
    i2s_install();
    i2s_setpin();
    i2s_start(I2S_PORT);
}
double fftAdd(int from, int to)
{
    int i = from;
    double result = 0;
    while (i <= to)
    {
        result += fftBin[i++];
    }
    return result;
}
void read_i2c_fft()
{

    delay(1); // DO NOT DELETE THIS LINE! It is needed to give the IDLE(0) task enough time and to keep the watchdog happy.
              // taskYIELD(), yield(), vTaskDelay() and esp_task_wdt_feed() didn't seem to work.
    EVERY_N_MILLISECONDS(180)
    {
        for (byte band = 0; band < NUM_BANDS; band++)
        {
            if (peakStripe[band] > 0)
            {
                peakStripe[band]--;
            }
            if (peakMatrix[band] > 0)
            {
                peakMatrix[band]--;
            }
        }
    }

    for (int i = 0; i < SAMPLES; i++)
    {
        int32_t digitalSample = 0;
        size_t bytes_read = 0;
        esp_err_t result = i2s_read(I2S_PORT, &digitalSample, sizeof(digitalSample), &bytes_read, /*portMAX_DELAY*/ 10);
        // int bytes_read = i2s_pop_sample(I2S_PORT, (char *)&digitalSample, portMAX_DELAY); // no timeout
        if (bytes_read > 0)
            micData = abs(digitalSample >> 16);

        vReal[i] = micData; // Store Mic Data in an array
        vImag[i] = 0;
    }

    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); // Weigh data
    FFT.Compute(FFT_FORWARD);                        // Compute FFT
    FFT.ComplexToMagnitude();                        // Compute magnitudes

    //
    // vReal[3 .. 255] contain useful data, each a 20Hz interval (60Hz - 5120Hz).
    // There could be interesting data at bins 0 to 2, but there are too many artifacts.
    //
    // FFT.MajorPeak(&FFT_MajorPeak, &FFT_Magnitude); // let the effects know which freq was most dominant

    for (int i = 0; i < SAMPLES; i++)
    { // Values for bins 0 and 1 are WAY too large. Might as well start at 3.
        double t = 0.0;
        t = abs(vReal[i]);
        t = t / 16.0; // Reduce magnitude. Want end result to be linear and ~4096 max.
        fftBin[i] = t;
        //  Serial.println(fftBin[i]);
    } // for()

    // Range
    fftCalc[0] = (fftAdd(2, 5)) / 2;      // 80 - 120
    fftCalc[1] = (fftAdd(5, 9)) / 3;      // 140 - 200
    fftCalc[2] = (fftAdd(9, 16)) / 5;     // 240 - 340  --  381
    fftCalc[3] = (fftAdd(16, 28)) / 8;    // 420 - 600
    fftCalc[4] = (fftAdd(29, 48)) / 12;   // 740 - 980
    fftCalc[5] = (fftAdd(48, 84)) / 21;   // 1280 - 1700
    fftCalc[6] = (fftAdd(84, 167)) / 37;  // 2220 - 2960
    fftCalc[7] = (fftAdd(167, 255)) / 62; // 3880 - 5120
    squelch = micSquelch / 10;
    // Noise supression of fftCalc bins using squelch adjustment for different input types.
    for (int i = 0; i < 8; i++)
    {
        fftCalc[i] = fftCalc[i] - (float)squelch * (float)linearNoise[i] / 4.0 <= 0 ? 0 : fftCalc[i];
    }

    // Adjustment for frequency curves.
    for (int i = 0; i < 8; i++)
    {
        fftCalc[i] = fftCalc[i] * fftResultPink[i];
    }
    gain = micSensytivity / 2;

    // Manual linear adjustment of gain using gain adjustment for different input types.
    for (int i = 0; i < 8; i++)
    {
        fftCalc[i] = fftCalc[i] * gain / 40 + fftCalc[i] / 16.0;
    }

    // Now, let's dump it all into fftResult. Need to do this, otherwise other routines might grab fftResult values prematurely.
    for (int i = 0; i < NUM_BANDS; i++)
    {
        bandValues[i] = constrain((int)fftCalc[i], 0, 254);
        spectrumByte[i] = map(constrain(bandValues[i], 0, 256), 0, 256, 0, 1024);
        stripeValues[i] = map(constrain(bandValues[i], 0, 256), 0, 256, 0, 75);
        matrixValues[i] = map(constrain(bandValues[i], 0, 256), 0, 256, 0, 16);
        // Move peak up
        if (stripeValues[i] > peakStripe[i])
        {
            peakStripe[i] = stripeValues[i];
        }
        if (matrixValues[i] > peakMatrix[i])
        {
            peakMatrix[i] = matrixValues[i];
        }
    }
}
const int samplingFrequency = 44100;
#define ADC_INPUT ADC1_CHANNEL_0
uint16_t offset = (int)ADC_INPUT * 0x1000 + 0xFFF;
#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))
size_t bytesRead = 0;
const int SAMPLEBLOCK = 1024;
int16_t samples[SAMPLEBLOCK];
float FreqBins[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int NoiseTresshold = 1500; // this will effect the upper bands most.
static int BandCutoffTable[16] = {40, 60, 100, 150, 250, 400, 650, 1000, 1600, 2500, 4000, 6250, 12000, 14000, 16000, 17000};
volatile float gVU = 0;   // Instantaneous read of VU value
volatile float oldVU = 0; // Previous read of VU value
int CalibrationType = 0;  // 0=none, 1=White, 2=Pink
char Filtername[4][6] = {
    "None", // see documentation on this one.
    "Pink",
    "White",
    "Brown"};

//static int BandCutoffTable[16] = {40, 60, 100, 150, 250, 400, 650, 1000, 1600, 2500, 4000, 6250, 12000, 14000, 16000, 17000};
static double BandCalibration_Pink[16] = {4.52, 5.48, 5.54, 6.06, 2.98, 1.72, 1.49, 1.36, 1.00, 1.49, 2.04, 1.71, 2.19, 2.68, 1.85, 5.69};
static double BandCalibration_White[16] = {169.55, 148.58, 141.29, 124.24, 35.59, 10.76, 6.97, 5.18, 2.89, 4.19, 4.24, 1.99, 1.00, 1.60, 1.53, 5.48};
static double BandCalibration_Brown[16] = {1.81, 2.17, 2.49, 2.89, 1.57, 1.00, 1.10, 1.30, 1.22, 3.74, 113.96, 774.90, 7.76, 645.75, 2583.00, 7749.00};
int BucketFrequency(int iBucket)
{
    if (iBucket <= 1)
        return 0;
    int iOffset = iBucket - 2;
    return iOffset * (samplingFrequency / 2) / (SAMPLEBLOCK / 2);
}

void i2s_read_fft2()
{

    i2s_read(I2S_PORT,
             (void *)samples,
             sizeof(samples),
             &bytesRead,     // workaround This is the actual buffer size last half will be empty but why?
             portMAX_DELAY); // no timeout

    if (bytesRead != sizeof(samples))
    {
        Serial.printf("Could only read %u bytes of %u in FillBufferI2S()\n", bytesRead, sizeof(samples));
        // return;
    }

    // ############ Step 2: compensate for Channel number and offset, safe all to vReal Array   ############
    for (uint16_t i = 0; i < ARRAYSIZE(samples); i++)
    {
        vReal[i] = offset - samples[i];
        vImag[i] = 0.0; // Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows

        // ############ Step 3: Do FFT on the VReal array  ############
        //  compute FFT
        FFT.DCRemoval();
        FFT.Windowing(vReal, SAMPLEBLOCK, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLEBLOCK, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLEBLOCK);
        FFT.MajorPeak(vReal, SAMPLEBLOCK, samplingFrequency);
        for (int i = 0; i < numBands; i++)
        {
            FreqBins[i] = 0;
        }
        // ############ Step 4: Fill the frequency bins with the FFT Samples ############
        float averageSum = 0.0f;
        for (int i = 2; i < SAMPLEBLOCK / 2; i++)
        {
            averageSum += vReal[i];
            if (vReal[i] > NoiseTresshold)
            {
                int freq = BucketFrequency(i);
                int iBand = 0;
                while (iBand < numBands)
                {
                    if (freq < BandCutoffTable[iBand])
                        break;
                    iBand++;
                }
                if (iBand > numBands)
                    iBand = numBands;
                FreqBins[iBand] += vReal[i];
                //  float scaledValue = vReal[i];
                //  if (scaledValue > peak[iBand])
                //    peak[iBand] = scaledValue;
            }
        }



        // ############ Step 5: Determine the VU value  and mingle in the readout...( cheating the bands ) ############ Step
        float t = averageSum / (SAMPLEBLOCK / 2);
        gVU = max(t, (oldVU * 3 + t) / 4);
        oldVU = gVU;

        // Serial.printf("gVu: %d\n",(int) gVU);

        for (int j = 0; j < numBands; j++)
        {
            if (CalibrationType == 1)
                FreqBins[j] *= BandCalibration_Pink[j];
            else if (CalibrationType == 2)
                FreqBins[j] *= BandCalibration_White[j];
            else if (CalibrationType == 3)
                FreqBins[j] *= BandCalibration_Brown[j];
        }
        for (int i = 0; i < numBands; i++)
        {
            Serial.print(FreqBins[i]);
        }
        Serial.printf("\n");
        Serial.printf("gVU: %d\n", (int) gVU);

    }