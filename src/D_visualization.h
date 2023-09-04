#pragma once

#include "D_include.h"

#define VISUALIZATION_PALETTE_SIZE 5
#define NUM_VISUALIZATIONS 4
#define SAMPLES 256 // Must be a power of 2
#define SAMPLING_FREQ 30000
#define AUDIO_IN_PIN 35 // Signal in on this pin
#define NUM_BANDS 16
#define MATRIX_WIDTH 32 // X-Dimension of the matrix
#define MATRIX_HEIGHT 8 // Y-Dimension of the matrix
#define FFT_ATTACK 0.5
#define FFT_RELEASE 0.6
uint8_t currentVisPattern = 0;
class Visualization
{
private:
    int currentVis; // Current visualization id

    arduinoFFT FFT;
    double fftReal[SAMPLES];                     // Real part of the fft
    double fftImag[SAMPLES];                     // Imaginary part of the fft
    double fftVal[MATRIX_WIDTH];                 // Actual fft values
    double fftPeak[MATRIX_WIDTH];                // Position of the peak (0 to 1)
    double fftPeakVal;                           // Value of the peak (0 to MATRIX_HEIGHT)
    CRGB palette[VISUALIZATION_PALETTE_SIZE];    // update colors: Background, colA, colB, colC, colD
    CRGB colorBuf[MATRIX_WIDTH * MATRIX_HEIGHT]; // Color buffer used by some visualizations

public:
    Visualization();

    double fftGain;

    void update(CRGB *leds);

    void nextVis();
    void prevVis();

    bool setPaletteColor(int index, CRGB color);
    CRGB getPaletteColor(int index);
    CRGB *getPalette();
};



Visualization::Visualization()
{
    currentVisPattern = 2;
    FFT = arduinoFFT(fftReal, fftImag, SAMPLES, SAMPLING_FREQ);
    fftGain = 0.0005;
}

void Visualization::update(CRGB *leds)
{

    // Store the dc offset of the captured signal
    int dcOffset = 0;

    // Capture some samples
    for (int i = 0; i < SAMPLES; i++)
    {
// Get the current mic input value
#ifdef VISUALIZATION_EMULATE_INPUT
        int val = random(400);
#else
        int val = analogRead(AUDIO_IN_PIN);
#endif

        // Set the real and imaginary part and update the dc offset
        fftReal[i] = val;
        fftImag[i] = 0;
        dcOffset += val;

        // Short delay to make equidistant captures
        delayMicroseconds(80);
    }

    // Remove the dc offset by subtracting it from all values
    dcOffset /= SAMPLES;
    for (int i = 0; i < SAMPLES; i++)
        fftReal[i] -= dcOffset;

    // Calculate the FFT
    FFT.Windowing(FFT_WIN_TYP_BLACKMAN_NUTTALL, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

    // Scale the frequency and amplitude and smooth out the fft

    fftPeakVal = 0;
    for (int x = 0; x < MATRIX_WIDTH; x++)
    {
        int sum = 0;
        double val = 0;

        // Average all nearby frequency bands to scale the frequency range to MATRIX_WIDTH
        double l = SAMPLES / (double)MATRIX_WIDTH / 2;
        for (int i = (int)(x * l); i < (x + 1) * l; i++)
        {
            val += fftReal[i];
            sum++;
        }

        // Scale the fft
        val *= fftGain / sum;
        val *= exp(x / (double)MATRIX_WIDTH);

        // val *= sqrt(val);

        // Keep the value in bounds and apply the attack and decay
        if (val < 0)
            val = 0;
        if (val > 1)
            val = 1;

        if (val > fftVal[x])
            fftVal[x] = fftVal[x] * FFT_ATTACK + val * (1 - FFT_ATTACK);
        else
            fftVal[x] = fftVal[x] * FFT_RELEASE + val * (1 - FFT_RELEASE);
        if (fftVal[x] > fftPeakVal)
        {
            fftPeakVal = fftVal[x];
            fftPeak[x] = x / (double)(MATRIX_WIDTH - 1);
        }
    }
    // // uint8_t StripePatternsAmount = ARRAY_SIZE(patternList) - 1;

    // // String named = patternList[1].Name;
    // patternList[currentStripePattern].update;
    // FastLED.show();
}

// void Visualization::nextVis()
// {
//     // Increase the visualization index
//     currentStripePattern++;
//     if (currentStripePattern >= NUM_VISUALIZATIONS)
//         currentStripePattern = 0;
// }

// void Visualization::prevVis()
// {
//     // Decrease the visualization index
//     currentStripePattern--;
//     if (currentStripePattern < 0)
//         currentStripePattern = NUM_VISUALIZATIONS - 1;
// }

// Getters and setters for the palette
bool Visualization::setPaletteColor(int index, CRGB color)
{
    if (index < 0 || index >= VISUALIZATION_PALETTE_SIZE)
        return false;
    palette[index] = color;
    return true;
}
CRGB Visualization::getPaletteColor(int index)
{
    if (index < 0 || index >= VISUALIZATION_PALETTE_SIZE)
        return palette[0];
    ;
    return palette[index];
}
CRGB *Visualization::getPalette()
{
    return palette;
}
