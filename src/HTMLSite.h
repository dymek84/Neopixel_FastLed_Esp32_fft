

#pragma once

#include "Imports.h"
#include <WebServer.h>
#include <ArduinoOTA.h>
uint8_t power = 1;
CRGBPalette16 gCurrentPalette(CRGB::Black);
// uint8_t gCurrentPaletteNumber = 0;
// uint8_t currentPaletteIndex = 0;
uint8_t currentPatternIndex = 0; // Index number of which pattern is current
uint8_t brightness = 125;
WebServer webserver(80);
typedef struct
{
    CRGBPalette16 palette;
    String name;
} PaletteAndName;
typedef PaletteAndName PaletteAndNameList[];

const CRGBPalette16 palettes[] = {
    RainbowColors_p,
    RainbowStripeColors_p,
    CloudColors_p,
    LavaColors_p,
    OceanColors_p,
    ForestColors_p,
    PartyColors_p,
    HeatColors_p};

const uint8_t paletteCount = ARRAY_SIZE(palettes);

const String paletteNames[paletteCount] = {
    "Rainbow",
    "Rainbow Stripe",
    "Cloud",
    "Lava",
    "Ocean",
    "Forest",
    "Party",
    "Heat",
};
void sendAll()
{
    String json = "{";

    json += "\"power\":" + String(power) + ",";
    json += "\"brightness\":" + String(brightness) + ",";

    json += "\"currentPattern\":{";
    json += "\"index\":" + String(currentPatternIndex);
    json += ",\"name\":\"" + patterns[currentPatternIndex].name + "\"}";

    json += ",\"currentPalette\":{";
    json += "\"index\":" + String(currentPaletteIndex);
    json += ",\"name\":\"" + paletteNames[currentPaletteIndex] + "\"}";

    json += ",\"patterns\":[";
    for (uint8_t i = 0; i < patternCount; i++)
    {
        json += "\"" + patterns[i].name + "\"";
        if (i < patternCount - 1)
            json += ",";
    }
    json += "]";

    json += ",\"palettes\":[";
    for (uint8_t i = 0; i < paletteCount; i++)
    {
        json += "\"" + paletteNames[i] + "\"";
        if (i < paletteCount - 1)
            json += ",";
    }
    json += "]";

    json += "}";

    webserver.send(200, "text/json", json);
    json = String();
}

void sendPower()
{
    String json = String(power);
    webserver.send(200, "text/json", json);
    json = String();
}

void sendPattern()
{
    String json = "{";
    json += "\"index\":" + String(currentPatternIndex);
    json += ",\"name\":\"" + patterns[currentPatternIndex].name + "\"";
    json += "}";
    webserver.send(200, "text/json", json);
    json = String();
}

void sendPalette()
{
    String json = "{";
    json += "\"index\":" + String(currentPaletteIndex);
    json += ",\"name\":\"" + paletteNames[currentPaletteIndex] + "\"";
    json += "}";
    webserver.send(200, "text/json", json);
    json = String();
}

void sendBrightness()
{
    String json = String(brightness);
    webserver.send(200, "text/json", json);
    json = String();
}

#define NUM_LEDS 50
void setPower(uint8_t value)
{
    power = value == 0 ? 0 : 1;
}

bool autoplayEnabled = false;
// increase or decrease the current pattern number, and wrap around at the ends
void adjustPattern(bool up)
{
    if (up)
        currentPatternIndex++;
    else
        currentPatternIndex--;

    // wrap around at the ends
    if (currentPatternIndex < 0)
        currentPatternIndex = patternCount - 1;
    if (currentPatternIndex >= patternCount)
        currentPatternIndex = 0;

    if (autoplayEnabled)
    {
        EEPROM.write(1, currentPatternIndex);
        EEPROM.commit();
    }
}

void setPattern(int value)
{
    // don't wrap around at the ends
    if (value < 0)
        value = 0;
    else if (value >= patternCount)
        value = patternCount - 1;

    currentPatternIndex = value;

    if (autoplayEnabled == 0)
    {
        EEPROM.write(1, currentPatternIndex);
        EEPROM.commit();
    }
}

void setPalette(int value)
{
    // don't wrap around at the ends
    if (value < 0)
        value = 0;
    else if (value >= paletteCount)
        value = paletteCount - 1;

    currentPaletteIndex = value;

    EEPROM.write(5, currentPaletteIndex);
    EEPROM.commit();
}

void setBrightness(int value)
{
    // don't wrap around at the ends
    if (value > 255)
        value = 255;
    else if (value < 0)
        value = 0;

    brightness = value;

    FastLED.setBrightness(brightness);

    EEPROM.write(0, brightness);
    EEPROM.commit();
}

void rainbowaaa()
{
    // FastLED's built-in rainbow generator
    fill_rainbow(stripe, NUM_LEDS, gHue, 10);
}
void addGlitter(fract8 chanceOfGlitter)
{
    if (random8() < chanceOfGlitter)
    {
        stripe[random16(NUM_LEDS)] += CRGB::White;
    }
}
void rainbowWithGlitter()
{
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow();
    addGlitter(80);
}

void confetti()
{
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(stripe, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    //  stripe[pos] += CHSV( gHue + random8(64), 200, 255);
    stripe[pos] += ColorFromPalette(palettes[currentPaletteIndex], gHue + random8(64));
}

void sinelon()
{
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(stripe, NUM_LEDS, 20);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    //  stripe[pos] += CHSV( gHue, 255, 192);
    stripe[pos] += ColorFromPalette(palettes[currentPaletteIndex], gHue, 192);
}

void bpm()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = palettes[currentPaletteIndex];
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++)
    { // 9948
        stripe[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void juggle()
{
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(stripe, NUM_LEDS, 20);
    byte dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        //    stripe[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
        stripe[beatsin16(i + 7, 0, NUM_LEDS)] |= ColorFromPalette(palettes[currentPaletteIndex], dothue);
        dothue += 32;
    }
}

// Pride2015 by Mark Kriegsman: https://gist.github.com/kriegsman/964de772d64c502760e5
// This function draws rainbows with an ever-changing,
// widely-varying set of parameters.
void pride()
{
    static uint16_t sPseudotime = 0;
    static uint16_t sLastMillis = 0;
    static uint16_t sHue16 = 0;

    uint8_t sat8 = beatsin88(87, 220, 250);
    uint8_t brightdepth = beatsin88(341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16; // gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 1, 3000);

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis;
    sLastMillis = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88(400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;

        brightnesstheta16 += brightnessthetainc16;
        uint16_t b16 = sin16(brightnesstheta16) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        CRGB newcolor = CHSV(hue8, sat8, bri8);

        nblend(stripe[i], newcolor, 64);
    }
}

// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves()
{
    static uint16_t sPseudotime = 0;
    static uint16_t sLastMillis = 0;
    static uint16_t sHue16 = 0;

    // uint8_t sat8 = beatsin88( 87, 220, 250);
    uint8_t brightdepth = beatsin88(341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16; // gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 300, 1500);

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis;
    sLastMillis = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88(400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for (uint16_t i = 0; i < NUM_LEDS; i++)
    {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;
        uint16_t h16_128 = hue16 >> 7;
        if (h16_128 & 0x100)
        {
            hue8 = 255 - (h16_128 >> 1);
        }
        else
        {
            hue8 = h16_128 >> 1;
        }

        brightnesstheta16 += brightnessthetainc16;
        uint16_t b16 = sin16(brightnesstheta16) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        uint8_t index = hue8;
        // index = triwave8( index);
        index = scale8(index, 240);

        CRGB newcolor = ColorFromPalette(gCurrentPalette, index, bri8);

        nblend(stripe[i], newcolor, 128);
    }
}

// Alternate rendering function just scrolls the current palette
// across the defined LED strip.
void palettetest()
{
    static uint8_t startindex = 0;
    startindex--;
    fill_palette(stripe, NUM_LEDS, startindex, (256 / NUM_LEDS) + 1, gCurrentPalette, 255, LINEARBLEND);
}
void loopSite()
{
    ArduinoOTA.handle();
    webserver.handleClient();
}

void setupSite()
{

    ArduinoOTA.onStart([]()
                       { Serial.println("Start"); });
    ArduinoOTA.onEnd([]()
                     { Serial.println("\nEnd"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
    ArduinoOTA.onError([](ota_error_t error)
                       {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed"); });
    ArduinoOTA.begin();

    webserver.serveStatic("/", SPIFFS, "/index.htm"); // ,"max-age=86400"

    webserver.on("/all", HTTP_GET, []()
                 { sendAll(); });

    webserver.on("/power", HTTP_GET, []()
                 { sendPower(); });

    webserver.on("/power", HTTP_POST, []()
                 {
    String value = webserver.arg("value");
    setPower(value.toInt());
    sendPower(); });

    webserver.on("/pattern", HTTP_GET, []()
                 { sendPattern(); });

    webserver.on("/pattern", HTTP_POST, []()
                 {
    String value = webserver.arg("value");
    setPattern(value.toInt());
    sendPattern(); });

    webserver.on("/patternUp", HTTP_POST, []()
                 {
    adjustPattern(true);
    sendPattern(); });

    webserver.on("/patternDown", HTTP_POST, []()
                 {
    adjustPattern(false);
    sendPattern(); });

    webserver.on("/brightness", HTTP_GET, []()
                 { sendBrightness(); });

    webserver.on("/brightness", HTTP_POST, []()
                 {
    String value = webserver.arg("value");
    setBrightness(value.toInt());
    sendBrightness(); });

    webserver.on("/palette", HTTP_GET, []()
                 { sendPalette(); });

    webserver.on("/palette", HTTP_POST, []()
                 {
    String value = webserver.arg("value");
    setPalette(value.toInt());
    sendPalette(); });

    webserver.serveStatic("/index.htm", SPIFFS, "/index.htm");
    webserver.serveStatic("/fonts", SPIFFS, "/fonts", "max-age=86400");
    webserver.serveStatic("/js", SPIFFS, "/js");
    webserver.serveStatic("/css", SPIFFS, "/css", "max-age=86400");
    webserver.serveStatic("/images", SPIFFS, "/images", "max-age=86400");
    webserver.serveStatic("/", SPIFFS, "/index.htm");

    webserver.begin();
}