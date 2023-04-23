
#pragma once

#include "Imports.h"

void createBands()
{
    EVERY_N_MILLISECONDS(60)
    {
        for (byte band = 0; band < NUM_BANDS; band++)
        {
            if (peakMatrix[band] > 0)
                peakMatrix[band]--;
            if (peakStripe[band] > 0)
                peakStripe[band]--;
        }
    }
    float amplitude = 150.0;
    int dmax = amplitude;
    for (int i = 0; i < NUM_BANDS; i++)
    {
        bandValues[i] = 0;
    }
    for (int i = 0; i < SAMPLES; i++)
    {
        newTimeForAudio = micros();
        vReal[i] = analogRead(MIC_IN_PIN);

        vImag[i] = 0;
        while ((micros() - newTimeForAudio) < sampling_period_us)
        {
        }
    }
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQ);
    for (int i = 2; i < (SAMPLES / 2); i++)
    {
        if (vReal[i] > 2000)
        { // Add a crude noise filter, 10 x amplitude or more
            uint8_t band = 0;
            if (i <= 2)
                band = 0; // 125Hz
            else if (i <= 5)
                band = 1; // 250Hz
            else if (i <= 13)
            {
                band = 2; // 500Hz
            }
            else if (i <= 27)
            {
                band = 3; // 1000Hz
            }
            else if (i <= 45)
            {
                band = 4; // 2000Hz
            }
            else if (i <= 152)
            {
                band = 5; // 4000Hz
            }
            else if (i <= 264)
            {
                band = 6; // 8000Hz
            }
            else
            {
                band = 7;
            }
            int dmax = amplitude;
            int dsize = (int)vReal[i] / amplitude;
            if (dsize > dmax)
                dsize = dmax;
            if (dsize > bandValues[band])
            {
                bandValues[band] = dsize;
            }

            bandValues[band] = ((oldBarHeights[band] * 1) + bandValues[band]) / 2;
            bandValues[band] = map(bandValues[band], 0, amplitude, 0, 75);
            oldBarHeights[band] = bandValues[band];
        }
    }
    for (int i = 0; i < NUM_BANDS; i++)
    {
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
void analyzeAudio()
{
    for (int i = 0; i < NUM_BANDS; i++)
    {
        bandValues[i] = 0;
    }
    for (int i = 0; i < SAMPLES; i++)
    {
        newTimeForAudio = micros();
        vReal[i] = analogRead(MIC_IN_PIN);

        vImag[i] = 0;
        while ((micros() - newTimeForAudio) < sampling_period_us)
        {
        }
    }
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQ);
    for (int i = 2; i < (SAMPLES / 2); i++)
    {
        if (vReal[i] > NOISE)
        {
            if (i <= 3)
                bandValues[0] += (int)vReal[i];
            if (i > 3 && i <= 6)
                bandValues[1] += (int)vReal[i];
            if (i > 6 && i <= 13)
                bandValues[2] += (int)vReal[i];
            if (i > 13 && i <= 27)
                bandValues[3] += (int)vReal[i];
            if (i > 27 && i <= 55)
                bandValues[4] += (int)vReal[i];
            if (i > 55 && i <= 112)
                bandValues[5] += (int)vReal[i];
            if (i > 112 && i <= 120)
                bandValues[6] += (int)vReal[i];
            if (i > 120)
                bandValues[7] += (int)vReal[i];
        }
    }
    for (int i = 0; i < NUM_BANDS; i++)
    {
        stripeValues[i] = map(constrain(bandValues[i], 0, 256), 0, 256, 0, 75);
        matrixValues[i] = map(constrain(bandValues[i], 0, 256), 0, 256, 0, 16);
    }
}

int audioSample()
{
    unsigned long startMillis = millis(); // Start of sample window
    unsigned int peakToPeak = 0;          // peak-to-peak level

    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    // collect data for 50 mS
    while (millis() - startMillis < sampleWindow)
    {
        sample = analogRead(MIC_IN_PIN);
        if (sample < 1024) // toss out spurious readings
        {
            if (sample > signalMax)
            {
                signalMax = sample; // save just the max levels
            }
            else if (sample < signalMin)
            {
                signalMin = sample; // save just the min levels
            }
        }
    }
    peakToPeak = signalMax - signalMin; // max - min = peak-peak amplitude
    // Serial.println(peakToPeak);
    double volts = (peakToPeak * 5.0) / 1024; // convert to volts
    int val = map(peakToPeak, 0, 1024, 0, NUM_LEDS_STRIPE);
    // Serial.println(val);
    return val;
}

#define MIN_SHOW_DELAY 15

const int BLOCK_SIZE = 64;

const int SAMPLE_RATE = 1024;

TaskHandle_t FFT_Task;

unsigned long microseconds;

double FFT_MajorPeak = 0;
double FFT_Magnitude = 0;
uint16_t mAvg = 0;

// These are the input and output vectors.  Input vectors receive computed results from FFT.

double fftBin[SAMPLES];

// Try and normalize fftBin values to a max of 4096, so that 4096/16 = 256.
// Oh, and bins 0,1,2 are no good, so we'll zero them out.
double fftCalc[8];
int fftResult[8];       // Our calculated result table, which we feed to the animations.
double fftResultMax[8]; // A table used for testing to determine how our post-processing is working.

// Table of linearNoise results to be multiplied by squelch in order to reduce squelch across fftResult bins.
int linearNoise[8] = {
    34,
    26,
    20,
    9,
    4,
    3,
    2,
    2,
};

// Table of multiplication factors so that we can even out the frequency response.
double fftResultPink[8] = {
    1.70,
    1.73,
    1.58,
    1.75,
    1.99,
    1.90,
    2.77,
    1.53,
};

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

void FFTcode()
{

    delay(1); // DO NOT DELETE THIS LINE! It is needed to give the IDLE(0) task enough time and to keep the watchdog happy.
              // taskYIELD(), yield(), vTaskDelay() and esp_task_wdt_feed() didn't seem to work.

    microseconds = micros();

    for (int i = 0; i < SAMPLES; i++)
    {
        vReal[i] = analogRead(MIC_IN_PIN); // A conversion takes about 9.7uS on an ESP32
        vImag[i] = 0;
        microseconds += sampling_period_us;
    }

    //  FFT.DCRemoval();
    //  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); // Weigh data
    //  FFT.Compute(FFT_FORWARD);                        // Compute FFT
    // FFT.ComplexToMagnitude();                        // Compute magnitudes

    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQ);

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
    } // for()

    /* This FFT post processing is a DIY endeavour. What we really need is someone with sound engineering expertise to do a great job here AND most importantly, that the animations look GREAT as a result.
     *
     * Andrew's updated mapping of 256 bins down to the 16 result bins with Sample Freq = 10240, samples = 512 and some overlap.
     * Based on testing, the lowest/Start frequency is 60 Hz (with bin 3) and a highest/End frequency of 5120 Hz in bin 255.
     * Now, Take the 60Hz and multiply by 1.320367784 to get the next frequency and so on until the end. Then detetermine the bins.
     * End frequency = Start frequency * multiplier ^ 16
     * Multiplier = (End frequency/ Start frequency) ^ 1/16
     * Multiplier = 1.320367784
     */
    int squelch = 0;
    int gain = 5;
    // Range
    fftCalc[0] = (fftAdd(3, 5)) / 2;      // 80 - 120
    fftCalc[1] = (fftAdd(5, 9)) / 3;      // 140 - 200
    fftCalc[2] = (fftAdd(9, 16)) / 5;     // 240 - 340
    fftCalc[3] = (fftAdd(16, 28)) / 8;    // 420 - 600
    fftCalc[4] = (fftAdd(29, 48)) / 12;   // 740 - 980
    fftCalc[5] = (fftAdd(48, 84)) / 21;   // 1280 - 1700
    fftCalc[6] = (fftAdd(84, 167)) / 37;  // 2220 - 2960
    fftCalc[7] = (fftAdd(167, 255)) / 62; // 3880 - 5120
    // Noise supression of fftCalc bins using squelch adjustment for different input types.
    for (int i = 0; i < 8; i++)
    {
        fftCalc[i] = fftCalc[i] - (float)squelch * (float)linearNoise[i] / 4.0 <= 0 ? 0 : fftCalc[i];
        //  Serial.println(fftCalc[i]);
    }

    // Adjustment for frequency curves.
    for (int i = 0; i < 8; i++)
    {
        fftCalc[i] = fftCalc[i] * fftResultPink[i];
    }
    // Manual linear adjustment of gain using gain adjustment for different input types.
    for (int i = 0; i < 8; i++)
    {
        fftCalc[i] = fftCalc[i] * gain / 40 + fftCalc[i] / 8.0;
    }

    // Now, let's dump it all into fftResult. Need to do this, otherwise other routines might grab fftResult values prematurely.
    for (int i = 0; i < 8; i++)
    {
        fftResult[i] = constrain((int)fftCalc[i], 0, 254);
    }
    for (int i = 0; i < NUM_BANDS; i++)
    {
        stripeValues[i] = map(constrain(fftResult[i], 0, 256), 0, 256, 0, 75);
        matrixValues[i] = map(constrain(fftResult[i], 0, 256), 0, 256, 0, 16);
    }

} // FFTcode()
void processAudio()
{
    //createBands();
    //analyzeAudio();
    FFTcode();
}

