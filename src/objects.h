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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_STRIPE, LED_PIN_STRIPE, NEO_GRB + NEO_KHZ800);

ThreeWire myWire(21, 22, 19); // 26 data, 27 clock e 25 reset do módulo RTC DS1302
RtcDS1302<ThreeWire> Rtc(myWire);
struct tm timeinfo;
RtcDateTime now;
