#pragma once

#include "Imports.h"

arduinoFFT FFT = arduinoFFT(); // Create FFT object

CRGB matrix[NUM_LEDS_MATRIX]; // Create LED Object
CRGB stripe[NUM_LEDS_STRIPE]; // Create LED Object
CLEDController *MatrtixController;
CLEDController *StripeController;

Adafruit_NeoMatrix AdafruitMatrix = Adafruit_NeoMatrix(32,
                                                       8,
                                                       MATRIX_DATA_PIN,
                                                       NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                                       NEO_GRB + NEO_KHZ800);

// FastLED_NeoMaxtrix - see https://github.com/marcmerlin/FastLED_NeoMatrix for
// Tiled Matrixes, Zig-Zag and so forth
FastLED_NeoMatrix *FastLedMatrix = new FastLED_NeoMatrix(
    matrix, MATRIX_WIDTH, MATRIX_HEIGHT, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);

// PREFERENCES
Preferences preferences; // We will store our variables here that we don't want to loose

AsyncWebServer server(HTTP_PORT);
AsyncWebSocket ws("/ws");

typedef void (*SimplePatterna)();
typedef SimplePatterna SimplePatternList[];
typedef struct
{
    SimplePatterna drawFrame;
    String name;
    bool isAudio;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_STRIPE, STRIPE_DATA_PIN, NEO_GRB + NEO_KHZ800);

struct tm timeinfo;
DateTime now;
RTC_DS1307 RTC;
