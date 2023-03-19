
#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <arduinoFFT.h>
#include <FastLED_NeoMatrix.h>
// #include "colorWipe.cpp"
// #include "pixelChase.cpp"
// #include "rainbow.h"

// #include "buttons.ino"
// #include "clock.ino"
#include "define.h"
#include "objects.h"
#include "colorsAndPallette.h"
#include "helperFuction.h"
#include "audioProcess.h"
#include "MatrixPatterns/AudioPatternsMatrix.h"
#include "StripePatterns/AudioPatternsStripe.h"

#include "MatrixPatterns/Enoise.h"
#include "StripePatterns/ripple.h"
#include "StripePatterns/pacifica.h"
#include "StripePatterns/salut.h"
#include "StripePatterns/plasma.h"

// WebThings
#include <WiFi.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h> // *OTA
#include <ArduinoJson.h>
// PREFERENCES
#include <Preferences.h> // Store the prefences in permanent memory in a much easier way than SPIFFS