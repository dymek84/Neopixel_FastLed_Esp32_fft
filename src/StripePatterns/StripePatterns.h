
#pragma once

#include "Imports.h"

long delayCW = 0;
void colorWipe(uint32_t colorW)
{
    if (millis() - delayCW > patternInterval)
    {
        //  Update delay time
        stripe[pixelCurrent] = CHSV(colorW, 255, 255); //  Set pixel's color (in RAM)
        FastLED.show();                                //  Update strip to match
        pixelCurrent++;                                //  Advance current pixel
        if (pixelCurrent >= NUM_LEDS_STRIPE)           //  Loop the pattern from the first LED
            pixelCurrent = 0;
        delayCW = millis();
    }
}

CRGBPalette16 pacifica_palette_1 =
    {0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
     0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50};
CRGBPalette16 pacifica_palette_2 =
    {0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
     0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F};
CRGBPalette16 pacifica_palette_3 =
    {0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33,
     0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF};

void pacifica_one_layer(CRGBPalette16 &p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
    uint16_t ci = cistart;
    uint16_t waveangle = ioff;
    uint16_t wavescale_half = (wavescale / 2) + 20;
    for (uint16_t i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        waveangle += 250;
        uint16_t s16 = sin16(waveangle) + 32768;
        uint16_t cs = scale16(s16, wavescale_half) + wavescale_half;
        ci += cs;
        uint16_t sindex16 = sin16(ci) + 32768;
        uint8_t sindex8 = scale16(sindex16, 240);
        CRGB c = ColorFromPalette(p, sindex8, bri, LINEARBLEND);
        stripe[i] += c;
    }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps()
{
    uint8_t basethreshold = beatsin8(9, 55, 65);
    uint8_t wave = beat8(40);

    for (uint16_t i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        uint8_t threshold = scale8(sin8(wave), 20) + basethreshold;
        wave += 7;
        uint8_t l = stripe[i].getAverageLight();
        if (l > threshold)
        {
            uint8_t overage = l - threshold;
            uint8_t overage2 = qadd8(overage, overage);
            stripe[i] += CRGB(overage, overage2, qadd8(overage2, overage2));
        }
    }
}
// Deepen the blues and greens
void pacifica_deepen_colors()
{
    for (uint16_t i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        stripe[i].blue = scale8(stripe[i].blue, 145);
        stripe[i].green = scale8(stripe[i].green, 200);
        stripe[i] |= CRGB(2, 5, 7);
    }
}
void pacifica_loop()
{
    // Increment the four "color index start" counters, one for each wave layer.
    // Each is incremented at a different speed, and the speeds vary over time.
    static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
    static uint32_t sLastms = 0;
    uint32_t ms = GET_MILLIS();
    uint32_t deltams = ms - sLastms;
    sLastms = ms;
    uint16_t speedfactor1 = beatsin16(3, 179, 269);
    uint16_t speedfactor2 = beatsin16(4, 179, 269);
    uint32_t deltams1 = (deltams * speedfactor1) / 256;
    uint32_t deltams2 = (deltams * speedfactor2) / 256;
    uint32_t deltams21 = (deltams1 + deltams2) / 2;
    sCIStart1 += (deltams1 * beatsin88(1011, 10, 13));
    sCIStart2 -= (deltams21 * beatsin88(777, 8, 11));
    sCIStart3 -= (deltams1 * beatsin88(501, 5, 7));
    sCIStart4 -= (deltams2 * beatsin88(257, 4, 6));

    // Clear out the LED array to a dim background blue-green
    fill_solid(stripe, NUM_LEDS_STRIPE, CRGB(2, 6, 10));

    // Render each of four layers, with different scales and speeds, that vary over time
    pacifica_one_layer(pacifica_palette_1, sCIStart1, beatsin16(3, 11 * 256, 14 * 256), beatsin8(10, 70, 130), 0 - beat16(301));
    pacifica_one_layer(pacifica_palette_2, sCIStart2, beatsin16(4, 6 * 256, 9 * 256), beatsin8(17, 40, 80), beat16(401));
    pacifica_one_layer(pacifica_palette_3, sCIStart3, 6 * 256, beatsin8(9, 10, 38), 0 - beat16(503));
    pacifica_one_layer(pacifica_palette_3, sCIStart4, 5 * 256, beatsin8(8, 10, 28), beat16(601));

    // Add brighter 'whitecaps' where the waves lines up more
    pacifica_add_whitecaps();

    // Deepen the blues and greens a bit
    pacifica_deepen_colors();
}

void rainbow()
{
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        for (uint16_t i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            stripe[i] = CRGB((i + gHue) & 255); //  Update delay time
        }
        FastLED.show();                 //  Update strip to match
                                        //  Loop the cycle back to the begining
        previousMillis = currentMillis; // time for next change to the display
    }
}

uint8_t max_bright = 128; // Overall brightness definition. It can be changed on the fly.
// Initialize our LED array. We'll be using less in operation.

struct ripple
{ // Reko Meriö's structures

    // Local definitions

    // Persistent local variables

    // Temporary local variables
    uint8_t brightness; // 0 to 255
    int8_t color;       // 0 to 255
    int16_t pos;        // -1 to NUM_LEDS  (up to 127 LED's)
    int8_t velocity;    // 1 or -1
    uint8_t life;       // 0 to 20
    uint8_t maxLife;    // 10. If it's too long, it just goes on and on. . .
    uint8_t fade;       // 192
    bool exist;         // 0 to 1

    void Move()
    {

        pos += velocity;
        life++;

        if (pos > NUM_LEDS_STRIPE - 1)
        { // Bounce back from far end.
            velocity *= -1;
            pos = NUM_LEDS_STRIPE - 1;
        }

        if (pos < 0)
        { // Bounce back from 0.
            velocity *= -1;
            pos = 0;
        }

        brightness = scale8(brightness, fade); // Adjust brightness accordingly to strip length

        if (life > maxLife)
            exist = false; // Kill it once it's expired.

    } // Move()

    void Init(uint8_t Fade, uint8_t MaxLife)
    { // Typically 216, 20

        pos = random16(NUM_LEDS_STRIPE / 20, NUM_LEDS_STRIPE - NUM_LEDS_STRIPE / 20); // Avoid spawning too close to edge.
        velocity = 1;                                                                 // -1 or 1
        life = 0;                                                                     // 0 to Maxlife
        maxLife = MaxLife;                                                            // 10 called
        exist = true;                                                                 // 0, 1
        brightness = 255;                                                             // 0 to 255
        color = millis();                                                             // hue;
        fade = Fade;                                                                  // 192 called

    } // Init()

}; // struct ripple

typedef struct ripple Ripple;

Ripple ripples[maxRipples];
void rippless()
{
    currentPatternName = "ripple";
    for (int i = 0; i < maxRipples; i += 2)
    { // Check to see if ripple has expired, and if so, create a new one.
        if (random8() > 224 && !ripples[i].exist)
        {                                  // Randomly create a new ripple if this one has expired.
            ripples[i].Init(232, 20);      // Initialize the ripple array with Fade and MaxLife values.
            ripples[i + 1] = ripples[i];   // Everything except velocity is the same for the ripple's other half. Position starts out the same for both halves.
            ripples[i + 1].velocity *= -1; // We want the other half of the ripple to go opposite direction.
        }
    }
    for (uint16_t l = 0; l < NUM_LEDS_STRIPE; l++)
    {
        stripe[l] = ColorFromPalette(currentPalette, colorTimer + l, 255, LINEARBLEND);
    }
    for (int i = 0; i < maxRipples; i++)
    { // Move the ripple if it exists
        if (ripples[i].exist)
        {
            stripe[ripples[i].pos] = ColorFromPalette(currentPalette, ripples[i].color, ripples[i].brightness, LINEARBLEND);
            ripples[i].Move();
        }
    }

    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 160);

} // rippless()

int s_start_pos[5];
int s_time[5] = {random(30), random(30), random(30), random(30), random(30)};
int s_color[5];
int s_brightness[5];
int s_tick[5] = {0, 0, 0, 0, 0};
int s_scale[5];
void salut(int s_count)
{
    static uint32_t prevTime;
    // стартовая позиция
    if (s_time[s_count] < s_tick[s_count])
    {
        s_time[s_count] = random(80) + 20;
        s_tick[s_count] = 0;
        s_start_pos[s_count] = random(NUM_LEDS_STRIPE);
        s_color[s_count] = random(255);
        s_brightness[s_count] = 255 - random(100);
        s_scale[s_count] = random(25) + 1;
    }

    s_tick[s_count]++;
    s_brightness[s_count] = s_brightness[s_count] - (s_brightness[s_count] / 12);
    s_color[s_count] = s_color[s_count] + 1;
    FOR_i(1, s_scale[s_count])
    {
        if ((s_start_pos[s_count] + s_tick[s_count] + i) < NUM_LEDS_STRIPE)
        {
            stripe[s_start_pos[s_count] + s_tick[s_count] + i] = CHSV(s_color[s_count], 255, s_brightness[s_count]);
        }
        if ((s_start_pos[s_count] - s_tick[s_count] - i) > 0)
        {
            stripe[s_start_pos[s_count] - s_tick[s_count] - i] = CHSV(s_color[s_count], 255, s_brightness[s_count]);
        }
    }
}

void theaterChase(uint32_t colorT)
{                                           // modified from Adafruit example to make it a state machine
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        static int j = 0, q = 0;
        static boolean on = true;
        if (on)
        {
            for (int i = 0; i < NUM_LEDS_STRIPE; i = i + 3)
            {
                stripe[i + q] = CHSV(colorT, 255, 255); // turn every third pixel on
                                                        /// stripe[i + q] = CHSV((i + j) % 255, 1));
            }
        }
        else
        {
            for (int i = 0; i < NUM_LEDS_STRIPE; i = i + 3)
            {
                stripe[i + q] = CHSV(0, 0, 0); // turn every third pixel off
            }
        }
        on = !on;       // toggel pixelse on or off for next time
        FastLED.show(); //  strip.show(); // display
        q++;            // update the q variable
        if (q >= 3)
        { // if it overflows reset it and update the J variable
            q = 0;
            j++;
            if (j >= 256)
                j = 0;
        }
        previousMillis = currentMillis; // Remember the time
    }
}

int pixelQueue = 0; // Pattern Pixel Queue
int pixelCycle = 0; // Pattern Pixel Cycle
long delayTC = 0;
void theaterChaseRainbow()
{
    if (millis() - delayTC > patternInterval)
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i += 3)
        {
            stripe[i + pixelQueue] = CHSV((i + pixelCycle) % 255, 255, 255); //  Update delay time
        }
        FastLED.show();
        for (int i = 0; i < NUM_LEDS_STRIPE; i += 3)
        {
            stripe[i + pixelQueue] = (0, 0, 0); //  Update delay time
        }
        pixelQueue++; //  Advance current queue
        pixelCycle++; //  Advance current cycle
        if (pixelQueue >= 3)
            pixelQueue = 0; //  Loop
        if (pixelCycle >= 256)
            pixelCycle = 0; //  Loop
        delayTC = millis();
    }
}