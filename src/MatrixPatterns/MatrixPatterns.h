
#pragma once

#include "Imports.h"

void Enoise()
{
  static bool eff = 1;
  EVERY_N_MILLISECONDS(25000) { eff ^= 1; } // speed of  effect change

  uint32_t ms = millis();

  for (byte y = 0; y < MATRIX_HEIGHT; y++)
  {
    for (byte x = 0; x < MATRIX_WIDTH; x++)
    {
      uint16_t pixelHue = inoise16((uint32_t)x * 5000, (uint32_t)y * 5000 + ms * 10, ms * 20);
      uint8_t pixelHue8 = inoise8(x * 15, y * 15 + ms / 8, ms / 70);
      matrix[XY(x, y)] = ColorFromPalette(currentPalette, pixelHue8 + ms / 20, 255, LINEARBLEND);
    }
  }

  FastLED.show();
}

void bpmMatrix()
{
  uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);

  for (int i = 0; i < NUM_LEDS_MATRIX; i++)
  {
    matrix[i] = ColorFromPalette(currentPalette, colorTimer + (i * 2), beat - colorTimer + (i * 10));
  }

  FastLED.show();
}
const PatternAndNameList patternsMatrix = {
    {Enoise, "Enoise"},
    {bpmMatrix, "BPM Matrix"},
};

const uint8_t MatrixPatternsAmount = ARRAY_SIZE(patternsMatrix);