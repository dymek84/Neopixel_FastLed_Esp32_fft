
#pragma once

#include "Imports.h"
void addGlitter(uint8_t chanceOfGlitter = 200)
{
    if (random8() < chanceOfGlitter)
    {
        stripe[random16(NUM_LEDS_STRIPE)] += CRGB::White;
    }
}
void colorWipe()
{

    //  Update delay time
    stripe[pixelCurrent] = CHSV(colorTimer, 255, 255); //  Set pixel's color (in RAM)
    FastLED.show();                                    //  Update strip to match
    pixelCurrent++;                                    //  Advance current pixel
    if (pixelCurrent >= NUM_LEDS_STRIPE)               //  Loop the pattern from the first LED
        pixelCurrent = 0;
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

uint8_t max_bright = 128; // Overall brightness definition. It can be changed on the fly.
// Initialize our LED array. We'll be using less in operation.

struct ripple
{ // Reko Meriö's structures

    // Local definitions

    // Persistent local variables

    // Temporary local variables
    uint8_t brightness; // 0 to 255
    int8_t color;       // 0 to 255
    int16_t pos;        // -1 to NUM_LEDS_STRIPE  (up to 127 LED's)
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
void salut()
{
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 64);
    int s_count = random16(1, 5);
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

void theaterChase()
{ // modified from Adafruit example to make it a state machine

    static int j = 0, q = 0;
    static boolean on = true;
    if (on)
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i = i + 3)
        {
            stripe[i + q] = CHSV(colorTimer + j, 255, 255); // turn every third pixel on
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
}

int pixelQueue = 0; // Pattern Pixel Queue
int pixelCycle = 0; // Pattern Pixel Cycle
void theaterChaseRainbow()
{
    int firstPixelHue = 0; // First pixel starts at red (hue 0)
    for (int a = 0; a < 30; a++)
    { // Repeat 30 times...
        for (int b = 0; b < 3; b++)
        {                                                     //  'b' counts from 0 to 2...
            fill_solid(stripe, NUM_LEDS_STRIPE, CRGB::Black); // fill red      //   Set all pixels in RAM to 0 (off)
            // 'c' counts up from 'b' to end of strip in increments of 3...
            for (int c = b; c < NUM_LEDS_STRIPE; c += 3)
            {
                // hue of pixel 'c' is offset by an amount to make one full
                // revolution of the color wheel (range 65536) along the length
                // of the strip (strip.numPixels() steps):
                int hue = firstPixelHue + c * 65536L / NUM_LEDS_STRIPE;

                stripe[c] = CHSV(hue, 255, 255); // Set pixel 'c' to value 'color'
            }
            FastLED.show();              // Update strip with new contents
            firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
        }
    }
}
void bpmStripe()
{
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);

    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        stripe[i] = ColorFromPalette(currentPalette, colorTimer + (i * 2), beat - colorTimer + (i * 10));
    }

    FastLED.show();
}
uint8_t active = 0;
void strobo()
{
    CRGB stripcolor = CRGB::Black;
    if (active == 0)
    {
        stripcolor = CRGB::Black;
        active = 1;
    }
    else
    {
        stripcolor = CRGB::White;
        active = 0;
    }
    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        stripe[i] = stripcolor;
    }
    FastLED.show();
}
// List of patterns to cycle through.  Each is defined as a separate function below.
void sinelon()
{
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 20);
    int pos2 = beatsin16(13, 0, NUM_LEDS_STRIPE - 1);
    stripe[pos2] += CHSV(colorTimer, 255, 255);
}
void juggle()
{
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 20);
    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        stripe[beatsin16(i + 7, 0, NUM_LEDS_STRIPE - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}
void confetti()
{
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 20);
    int pos2 = random16(NUM_LEDS_STRIPE);
    stripe[pos2] += CHSV(gHue + random8(64), 200, 255);
}

void rainbow()
{
    fill_rainbow(stripe, NUM_LEDS_STRIPE, gHue, 7);
}

void rainbowWithGlitter()
{
    rainbow();
    addGlitter(80);
}
uint8_t sparking = 120;
uint8_t cooling = 50;
// based on FastLED example Fire2012WithPalette: https://github.com/FastLED/FastLED/blob/master/examples/Fire2012WithPalette/Fire2012WithPalette.ino
void heatMap(CRGBPalette16 palette, bool up)
{
    fill_solid(stripe, NUM_LEDS_STRIPE, CRGB::Black);

    // Add entropy to random number generator; we use a lot of it.
    random16_add_entropy(random(256));

    // Array of temperature readings at each simulation cell
    static byte heat[NUM_LEDS_STRIPE];

    byte colorindex;

    // Step 1.  Cool down every cell a little
    for (uint16_t i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / NUM_LEDS_STRIPE) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (uint16_t k = NUM_LEDS_STRIPE - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < sparking)
    {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for (uint16_t j = 0; j < NUM_LEDS_STRIPE; j++)
    {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        colorindex = scale8(heat[j], 190);

        CRGB color = ColorFromPalette(palette, colorindex);

        if (up)
        {
            stripe[j] = color;
        }
        else
        {
            stripe[(NUM_LEDS_STRIPE - 1) - j] = color;
        }
    }
}
const PatternAndNameList patternsStripe = {
    {stripeVuBandsSolidColor, "Stripe_Vu_Bands_Solid-Color"},
    {stripeVuBandsColors, "Vu_Bands_Colors"},
    {stripeVuBandsBeatsin, "Vu_Bands_ Beatsin"},
    {colorWipe, "colorWipe"},
    {pacifica_loop, "Pacifica"},
    {rainbow, "Rainbow"},
    {rippless, "Ripple"},
    {salut, "Salut"},
    {theaterChase, "Theater_Chase"},
    {theaterChaseRainbow, "Theater_Chase_Rainbow"},
    {bpmStripe, "BPM_Stripe"},
    //{displayUpdateStripe, "Display_Update_Stripe"},
    {sinelon, "Sinelon"},
    {juggle, "Juggle"},
    {strobo, "Strobo"},
    {VUStripe, "VUStripe"},
    {confetti, "Confetti"},
    {rainbowWithGlitter, "Rainbow_With_Glitter"}};

const uint8_t StripePatternsAmount = ARRAY_SIZE(patternsStripe);