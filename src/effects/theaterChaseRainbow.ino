
#pragma once

#include "Imports.h"
int pixelQueue = 0; // Pattern Pixel Queue
int pixelCycle = 0; // Pattern Pixel Cycle
long delayTC = 0;
void theaterChaseRainbow()
{
    if (millis() - delayTC > patternInterval)
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i += 3)
        {
            stripe[i + pixelQueue] = CHSV((i + pixelCycle) % 255, 255, 255); //  Update delay time
        }
        FastLED.show();
        for (int i = 0; i < NUM_LEDS_STRIPE; i += 3)
        {
            stripe[i + pixelQueue] = (0, 0, 0); //  Update delay time
        }
        pixelQueue++; //  Advance current queue
        pixelCycle++; //  Advance current cycle
        if (pixelQueue >= 3)
            pixelQueue = 0; //  Loop
        if (pixelCycle >= 256)
            pixelCycle = 0; //  Loop
        delayTC = millis();
    }
}