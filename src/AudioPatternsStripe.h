
#pragma once

#include "Imports.h"

void VUStripe()
{
    int signalAvg = audioSample();
    EVERY_N_MILLISECONDS(5)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 60); // Fade out pixels.
    }
    uint16_t pos = beat8(signalAvg) % NUM_LEDS_STRIPE; // modulo the position to be within NUM_LEDS
    stripe[pos] = CHSV(colorTimer, 200, 255);
}

void water_fall_vu()
{
    // #define chanel_water 5;

    analyzeAudio();

    int complex_wave = vReal[SAMPLES / 8] + vReal[SAMPLES / 2] + vReal[SAMPLES - (SAMPLES / 8)];
    complex_wave += vReal[5];
    complex_wave = constrain(map(complex_wave, 0, 16000, 0, 255), 0, 255);
    stripe[(NUM_LEDS_STRIPE / 2) - 1] = CHSV(complex_wave, 255, complex_wave);
    stripe[(NUM_LEDS_STRIPE / 2) + 1] = CHSV(complex_wave, 255, complex_wave);
    FOR_i(0, NUM_LEDS_STRIPE / 2 - 1)
    {
        stripe[i] = stripe[i + 1];
        stripe[NUM_LEDS_STRIPE - i] = stripe[(NUM_LEDS_STRIPE - i) - 1];
    }
    FastLED.show();
}