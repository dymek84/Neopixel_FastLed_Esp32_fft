
#pragma once

#include "Imports.h"

void rainbowBars(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= TOP - barHeight; y--)
        {
            FastLedMatrix->drawPixel(x, y,
                                     CHSV((x / BAR_WIDTH) * (255 / NUM_BANDS), 255, 255));
        }
    }
}
