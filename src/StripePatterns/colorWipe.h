
#pragma once

#include "Imports.h"

long delayCW = 0;
void colorWipe(uint32_t colorW)
{
    if (millis() - delayCW > patternInterval)
    {
        //  Update delay time
        stripe[pixelCurrent] = CHSV(colorW, 255, 255); //  Set pixel's color (in RAM)
        FastLED.show();                                //  Update strip to match
        pixelCurrent++;                                //  Advance current pixel
        if (pixelCurrent >= NUM_LEDS_STRIPE)           //  Loop the pattern from the first LED
            pixelCurrent = 0;
        delayCW = millis();
    }
}