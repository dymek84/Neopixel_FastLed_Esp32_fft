
#pragma once

#include "Imports.h"


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
        bandValues[i] = map(constrain(bandValues[i], 0, 256), 0, 256, 0, 75);
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
