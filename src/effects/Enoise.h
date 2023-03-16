
#pragma once

#include "Imports.h"

void Enoise(ledTypeConnected whichLeds)
{
  // Serial.println("Enoise");
  currentPatternName = "Enoise";
  static bool eff = 1;
  EVERY_N_MILLISECONDS(25000) { eff ^= 1; } // speed of  effect change

  uint32_t ms = millis();

  for (byte y = 0; y < MATRIX_HEIGHT; y++)
  {
    for (byte x = 0; x < MATRIX_WIDTH; x++)
    {
      uint16_t pixelHue = inoise16((uint32_t)x * 5000, (uint32_t)y * 5000 + ms * 10, ms * 20);
      uint8_t pixelHue8 = inoise8(x * 15, y * 15 + ms / 8, ms / 70);
      matrix[XY(x, y)] = ColorFromPalette(gCurrentPalette, pixelHue8 + ms / 20, 255, LINEARBLEND);
    }
  }

  FastLED.show();
}
