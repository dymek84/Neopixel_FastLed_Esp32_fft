
#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <arduinoFFT.h>
#include <FastLED_NeoMatrix.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// WebThings

#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

#include <ArduinoJson.h>
// #include <ESPmDNS.h>
// #include <HTTPClient.h>      // Needed to get some information from the internetz.. .like weather data
// #include <AsyncElegantOTA.h> // A library to allow Over The Air Updates :)
//  PREFERENCES
#include <Preferences.h> // Store the prefences in permanent memory in a much easier way than SPIFFS
#include "main.h"
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

#include "MatrixPatterns/MatrixPatterns.h"
#include "StripePatterns/StripePatterns.h"

// #include "WebThings.h"

#include "testweb.h"