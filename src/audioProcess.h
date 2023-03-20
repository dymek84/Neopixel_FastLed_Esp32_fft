
#pragma once

#include "Imports.h"

void getSamples()
{
    for (int i = 0; i < NUM_BANDS; i++)
    {
        bandValues[i] = 0;
    }
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
    for (int i = 2; i < (NUM_BANDS * Displacement) + 2; i += Displacement)
    {
        vReal[i] = constrain(vReal[i], 0, 2047);            // set max value for input data
        vReal[i] = map(vReal[i], 0, 2047, 0, MATRIX_WIDTH); // map data to fit our display

        bandValues[(i / Displacement) - 2]--;              // Decrease displayed value
        if (vReal[i] > bandValues[(i / Displacement) - 2]) // Match displayed value to measured value
            bandValues[(i / Displacement) - 2] = vReal[i];
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
        vReal[i] = analogRead(AUDIO_IN_PIN);

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
            if (i <= 2)
                bandValues[0] += (int)vReal[i];
            if (i >= 2 && i <= 3)
                bandValues[1] += (int)vReal[i];
            if (i >= 3 && i <= 4)
                bandValues[2] += (int)vReal[i];
            if (i >= 4 && i <= 5)
                bandValues[3] += (int)vReal[i];
            if (i >= 5 && i <= 6)
                bandValues[4] += (int)vReal[i];
            if (i >= 6 && i <= 7)
                bandValues[5] += (int)vReal[i];
            if (i >= 7 && i <= 8)
                bandValues[6] += (int)vReal[i];
            if (i >= 8 && i <= 9)
                bandValues[7] += (int)vReal[i];
            if (i >= 9 && i <= 10)
                bandValues[8] += (int)vReal[i];
            if (i >= 10 && i <= 11)
                bandValues[9] += (int)vReal[i];
            if (i >= 11 && i <= 12)
                bandValues[10] += (int)vReal[i];
            if (i >= 12 && i <= 13)
                bandValues[11] += (int)vReal[i];
            if (i >= 13 && i <= 14)
                bandValues[12] += (int)vReal[i];
            if (i >= 14 && i <= 15)
                bandValues[13] += (int)vReal[i];
            if (i >= 15 && i <= 16)
                bandValues[14] += (int)vReal[i];
            if (i >= 16 && i <= 17)
                bandValues[15] += (int)vReal[i];
            if (i >= 17 && i <= 18)
                bandValues[16] += (int)vReal[i];
            if (i >= 18 && i <= 20)
                bandValues[17] += (int)vReal[i];
            if (i >= 20 && i <= 24)
                bandValues[18] += (int)vReal[i];
            if (i >= 24 && i <= 28)
                bandValues[19] += (int)vReal[i];
            if (i >= 28 && i <= 34)
                bandValues[20] += (int)vReal[i];
            if (i >= 34 && i <= 40)
                bandValues[21] += (int)vReal[i];
            if (i >= 40 && i <= 47)
                bandValues[22] += (int)vReal[i];
            if (i >= 47 && i <= 55)
                bandValues[23] += (int)vReal[i];
            if (i >= 55 && i <= 65)
                bandValues[24] += (int)vReal[i];
            if (i >= 65 && i <= 88)
                bandValues[25] += (int)vReal[i];
            if (i >= 88 && i <= 120)
                bandValues[26] += (int)vReal[i];
            if (i >= 120 && i <= 160)
                bandValues[27] += (int)vReal[i];
            if (i >= 160 && i <= 190)
                bandValues[28] += (int)vReal[i];
            if (i >= 190 && i <= 248)
                bandValues[29] += (int)vReal[i];
            if (i >= 150 && i <= 178)
                bandValues[30] += (int)vReal[i];
            if (i >= 178 && i <= 210)
                bandValues[31] += (int)vReal[i];
        }
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
        sample = analogRead(AUDIO_IN_PIN);
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
