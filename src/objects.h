#pragma once

#include "Imports.h"

arduinoFFT FFT = arduinoFFT(); // Create FFT object

CRGB matrix[NUM_LEDS_MATRIX]; // Create LED Object
CRGB stripe[NUM_LEDS_STRIPE]; // Create LED Object

Adafruit_NeoMatrix AdafruitMatrix = Adafruit_NeoMatrix(32,
                                                       8,
                                                       LED_PIN_MATRIX,
                                                       NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                                       NEO_GRB + NEO_KHZ800);

// FastLED_NeoMaxtrix - see https://github.com/marcmerlin/FastLED_NeoMatrix for
// Tiled Matrixes, Zig-Zag and so forth
FastLED_NeoMatrix *FastLedMatrix = new FastLED_NeoMatrix(
    matrix, MATRIX_WIDTH, MATRIX_HEIGHT, NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);

IPAddress ip(1, 2, 3, 4);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);

// MULTI CPU TASKS
TaskHandle_t Wifimode; // CONTAINER USED FOR TASKS
TaskHandle_t APmode;   // CONTAINER USED FOR TASKS (aka threads, but slightly different)