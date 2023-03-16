#pragma once

#include "Imports.h"

arduinoFFT FFT = arduinoFFT(); // Create FFT object
CRGB matrix[NUM_LED_MATRIX];   // Create LED Object
CRGB stripe[NUM_LEDS_STRIPE];  // Create LED Object
Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(32,
                                                8,
                                                LED_PIN_MATRIX,
                                                NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                                NEO_GRB + NEO_KHZ800);


// FastLED_NeoMaxtrix - see https://github.com/marcmerlin/FastLED_NeoMatrix for
// Tiled Matrixes, Zig-Zag and so forth
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(
    leds, MATRIX_WIDTH, MATRIX_HEIGHT, NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);
