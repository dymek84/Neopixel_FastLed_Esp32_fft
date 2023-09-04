#pragma once

#include "Imports.h"

void setNum(byte number, byte pos)
{
    if ((millis() / 1000) % 2 == 0)
    {
        matrix[MatrixArray[2][14]] = CRGB::Wheat;
        matrix[MatrixArray[1][14]] = CRGB::Wheat;
        matrix[MatrixArray[5][14]] = CRGB::Wheat;
        matrix[MatrixArray[4][14]] = CRGB::Wheat;
    }
    else
    {
    }
    if (pos == 0)
        pos = 2; // change pos to the real location in the array
    else if (pos == 1)
        pos = 8;
    else if (pos == 2)
        pos = 16;
    else if (pos == 3)
        pos = 22;
    for (int x = 0; x < 6; x++)
    { // now place the digit's 6x8 font in the display buffer
        for (int y = 0; y < 8; y++)
        {
            if (num[number][y] & (0b01000000 >> x))
                matrix[MatrixArray[y][pos + x]] = CRGB::Wheat;
        }
    }
}
