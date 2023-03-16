#pragma once

#include "Imports.h"

void SetLeftStripe(int i, uint32_t color)
{
    stripe[NUM_LEDS_STRIPE / 2 + i] = CHSV(color, 255, 255);
}
void SetRightStripe(int i, uint32_t color)
{
    stripe[NUM_LEDS_STRIPE / 2 - i] = CHSV(color, 255, 255);
}