
#include <Arduino.h>

#pragma once

#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <driver/i2s.h>
#include <arduinoFFT.h>
#include <FastLED_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "Time.h"
#include "RTClib.h"

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <Preferences.h>

#include "main.h"

#include "define.h"
#include "objects.h"
#include "colorsAndPallette.h"
#include "helperFuction.h"

#include "audioProcess.h"
#include "displayClock.h"

#include "StripePatterns/twinklefox.h"
#include "MatrixPatterns/MatrixPatterns.h"
#include "StripePatterns/StripePatterns.h"
#include "StripeGames/randomGame.h"
#include "WebThings.h"