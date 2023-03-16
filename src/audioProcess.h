
#pragma once

#include "Imports.h"

void getSamples()
{
    for (int i = 0; i < SAMPLES; i++)
    {
        vReal[i] = analogRead(AUDIO_IN_PIN) * MULTIPLY_BY;
        vImag[i] = 0;
    }

    // FFT
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    // Update Intensity Array
    for (int i = 2; i < (6 * Displacement) + 2; i += 2)
    {
        vReal[i] = constrain(vReal[i], 0, 2047);            // set max value for input data
        vReal[i] = map(vReal[i], 0, 2047, 0, MATRIX_WIDTH); // map data to fit our display

        Intensity[(i / Displacement) - 2]--;              // Decrease displayed value
        if (vReal[i] > Intensity[(i / Displacement) - 2]) // Match displayed value to measured value
            Intensity[(i / Displacement) - 2] = vReal[i];
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
        newTime = micros();
        vReal[i] = analogRead(AUDIO_IN_PIN);

        vImag[i] = 0;
        while ((micros() - newTime) < sampling_period_us)
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
            if (i > 112 && i <= 229)
                bandValues[6] += (int)vReal[i];
            if (i > 229)
                bandValues[7] += (int)vReal[i];
        }
    }
}
