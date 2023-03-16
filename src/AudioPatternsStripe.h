
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
        vReal[i] = constrain(vReal[i], 0, 2047);    // set max value for input data
        vReal[i] = map(vReal[i], 0, 2047, 0, MATRIX_HEIGHT); // map data to fit our display

        Intensity[(i / Displacement) - 2]--;              // Decrease displayed value
        if (vReal[i] > Intensity[(i / Displacement) - 2]) // Match displayed value to measured value
            Intensity[(i / Displacement) - 2] = vReal[i];
    }
}