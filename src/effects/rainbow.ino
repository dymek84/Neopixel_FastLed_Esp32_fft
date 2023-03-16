

#pragma once

#include "Imports.h"

void rainbow()
{
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        for (uint16_t i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            stripe[i] = CRGB((i + gHue) & 255); //  Update delay time
        }
        FastLED.show(); //  Update strip to match
                        //  Loop the cycle back to the begining
        previousMillis = currentMillis; // time for next change to the display
    }
}
