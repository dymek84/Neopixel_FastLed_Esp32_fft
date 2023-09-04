
#pragma once

#include "Imports.h"
void addGlitter(uint8_t chanceOfGlitter = 200)
{
    if (random8() < chanceOfGlitter)
    {
        stripe[random16(NUM_LEDS_STRIPE)] += CRGB::White;
    }
}

void twinkleFox()
{

    static int tspeed = 6;
    static int tdensity = 1;

    EVERY_N_SECONDS(10)
    {
        // chooseNextColorPalette(targetTwinklePalette);

        tspeed = max((tspeed + 1) % 9, 6);
        tdensity = max((tdensity + 1) % 9, 1);
        //    PRINTX("Speed:", tspeed);
        //   PRINTX("Density:", tdensity);
    }
    drawTwinkles(5, 5);
}
byte colorForWipe;
void colorWipe()
{
    for (uint8_t i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        stripe[i] = CHSV(colorForWipe, 255, 255);
    }
    if (stripeValues[0] > 30)
    {
        colorForWipe += 16;
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
        stripe[l] = ColorFromPalette(currentPaletteStripe, colorHueStripe + l, 255, LINEARBLEND);
    }
    for (int i = 0; i < maxRipples; i++)
    { // Move the ripple if it exists
        if (ripples[i].exist)
        {
            stripe[ripples[i].pos] = ColorFromPalette(currentPaletteStripe, ripples[i].color, ripples[i].brightness, LINEARBLEND);
            ripples[i].Move();
        }
    }

    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 160);

} // rippless()

void theaterChase()
{ // modified from Adafruit example to make it a state machine

    static int j = 0, q = 0;
    static boolean on = true;
    if (on)
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i = i + 3)
        {
            stripe[i + q] = CHSV(colorHueStripe + j, 255, 255); // turn every third pixel on
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

void bpmStripe()
{
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);

    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        stripe[i] = ColorFromPalette(currentPaletteStripe, colorHueStripe + (i * 2), beat - colorHueStripe + (i * 10));
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
    FastLED.delay(patternInterval);
}
// List of patterns to cycle through.  Each is defined as a separate function below.
void sinelon()
{
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 20);
    int pos2 = beatsin16(13, 0, NUM_LEDS_STRIPE - 1);
    stripe[pos2] += CHSV(colorHueStripe, 255, 255);
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
    stripe[pos2] += CHSV(colorHueStripe + random8(64), 200, 255);
}

void rainbow()
{
    fill_rainbow(stripe, NUM_LEDS_STRIPE, colorHueStripe, 7);
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
void heatMapShow()
{
    heatMap(currentPaletteStripe, true);
}

void displayUpdateStripe()
{
    // analyzeAudio();
    uint16_t color;

    for (int i = 0; i < NUM_BANDS; i++)
    {
        color += 255 / NUM_BANDS;
        for (int j = NUM_BANDS * i; j < NUM_BANDS * i + 50; j++)
        {
            // Serial.println(stripeValues[i]);
            if (j <= (map(stripeValues[i], 0, 255, 0, 50) + NUM_BANDS * i))
            { // Light everything within the intensity range

                stripe[NUM_BANDS * (i + 1) - j - 1] = CHSV(color, 255, BRIGHTNESS);
            }
            else
            {

                stripe[NUM_BANDS * (i + 1) - j - 1] = CHSV(color, 255, 0);
            }
        }
    }
}
int peaksStripe[8] = {};
void stripeVuBandsSolidColor()
{

    // analyzeAudio();
    //  createBands();
    for (uint8_t x = 0; x < 8; x++)
    {
        if (stripeValues[x] > peaksStripe[x])
        {
            // push the peaks higher
            peaksStripe[x] = stripeValues[x];
        }
        for (int i = 0; i < 37; i++)
        {
            int on = 75 + x * 150;
            if (i < stripeValues[x])
            {
                stripe[on + i] = CHSV(16 * x, 255, 255);
                stripe[on - i] = CHSV(16 * x, 255, 255);
            }
            else
            {
                stripe[on + i] = CHSV(0, 0, 0);
                stripe[on - i] = CHSV(0, 0, 0);
            }
            if (i == peaksStripe[x])
            {
                stripe[on + i] = CRGB::White;
                stripe[on - i] = CRGB::White;
            }
            if (i == 0)
            {
                stripe[on + i] = CHSV(16 * x, 255, 255);
                stripe[on - i] = CHSV(16 * x, 255, 255);
            }
        }
    }
    EVERY_N_MILLISECONDS(120)
    {
        for (byte band = 0; band < NUM_BANDS; band++)
        {
            if (peaksStripe[band] > 0)
                peaksStripe[band]--;
        }
    }
}

void stripeVuBandsBeatsin()
{
    // processAudio();

    // fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 125); // Fade out pixels.
    for (uint8_t x = 0; x < 8; x++)
    {
        for (int i = 0; i < 75; i++)
        {
            int on = 75 + x * 150;
            input_vu[x] = stripeValues[x];
            if (result_vu[x] < input_vu[x])
            {
                result_vu[x] = result_vu[x] + ((input_vu[x] - result_vu[x]) * 0.9); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
            }
            else
            {
                result_vu[x] = result_vu[x] - ((result_vu[x] - input_vu[x]) * 0.1); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
            }
            if (i < result_vu[x])
            {
                stripe[on + i] = CHSV(beatsin8(30, 0, 255, 0, i * x / 4), 255, 255);
                stripe[on - i] = CHSV(beatsin8(30, 0, 255, 0, i * x / 4), 255, 255);
            }
            else
            {
                stripe[on + i] = CHSV(beatsin8(30, 0, 255, 0, i * x / 4), 255, 0);
                stripe[on - i] = CHSV(beatsin8(30, 0, 255, 0, i * x / 4), 255, 0);
            }
        }
    }
}
void stripeVuBandsColors()
{
    // processAudio();
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 125); // Fade out pixels.
    for (uint8_t x = 0; x < 8; x++)
    {
        for (int i = 0; i < 75; i++)
        {
            int on = 75 + x * 150;

            if (i < stripeValues[x])
            {
                stripe[on + i] = CHSV(colorHueStripe + (x * 32), 255, BRIGHTNESS);
                stripe[on - i] = CHSV(colorHueStripe + (x * 32), 255, BRIGHTNESS);
            }
            else
            {
                // stripe[on - i] = CHSV(colorHueStripe + (x * 32), 255, 0);
                // stripe[on + i] = CHSV(colorHueStripe + (x * 32), 255, 0);
            }
            /*  if (i < stripeValues[1])
              {
                  stripe[225 + i] = CHSV(colorHueStripe + 25, 255, BRIGHTNESS);
                  stripe[225 - i] = CHSV(colorHueStripe + 25, 255, BRIGHTNESS);
              }
              else
              {
                  stripe[225 - i] = CHSV(colorHueStripe + 25, 255, 0);
                  stripe[225 + i] = CHSV(colorHueStripe + 25, 255, 0);
              }*/
        }
    }
}

// function used by "fadeTowardColor"
void nblendU8TowardU8(uint8_t &cur, const uint8_t target, uint8_t amount)
{
    if (cur == target)
        return;

    if (cur < target)
    {
        uint8_t delta = target - cur;
        delta = scale8_video(delta, amount);
        cur += delta;
    }
    else
    {
        uint8_t delta = cur - target;
        delta = scale8_video(delta, amount);
        cur -= delta;
    }
}
// Functions from Kriegsman example
CRGB fadeTowardColor(CRGB &cur, const CRGB &target, uint8_t amount)
{
    nblendU8TowardU8(cur.red, target.red, amount);
    nblendU8TowardU8(cur.green, target.green, amount);
    nblendU8TowardU8(cur.blue, target.blue, amount);
    return cur;
}

void beatDetector()
{
    if (matrixValues[0] + matrixValues[1] > 20)
    {
        int strt = random16(NUM_LEDS_STRIPE / 2);        // Start of FastLED stuff. Get a starting point.
        int ende = strt + random16(NUM_LEDS_STRIPE / 2); // And and end point.
        for (int i = strt; i < ende; i++)
        {
            uint8_t index = inoise8(i * 30, millis() + i * 30);                          // Make Perlin noise beteween those points.
            stripe[i] = ColorFromPalette(currentPaletteStripe, index, 255, LINEARBLEND); // And display it with palettes.
        }
    }

    EVERY_N_MILLIS(50)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 64); // Fade the LED's
                                                    // FastLED.show();                             // We can't show too often, or things break.
    }
}
void spectrumDetector()
{
    for (uint8_t x = 0; x < 8; x++)
    {
        // NUM_LEDS_STRIPE / 16 (bands*2) = 61,75
        int beat = 8;
        if (x > 2 && x < 5)
        {
            beat = 6;
        }
        if (matrixValues[x] > beat)
        {
            int strt = random16(30);        // Start of FastLED stuff. Get a starting point.
            int ende = strt + random16(31); // And and end point.
            for (int i = strt; i < ende; i++)
            {
                uint8_t index = inoise8(i * 30, millis() + i * 30); // Make Perlin noise beteween those points.
                stripe[i + x * 61] = ColorFromPalette(currentPaletteStripe, x * 32, 255, LINEARBLEND);
                stripe[NUM_LEDS_STRIPE - (i + x * 61)] = ColorFromPalette(currentPaletteStripe, x * 32, 255, LINEARBLEND); // And display it with palettes.
            }
        }
    }
    EVERY_N_MILLIS(50)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 64); // Fade the LED's
                                                    // FastLED.show();                             // We can't show too often, or things break.
    }
}
void water_fall_vu()
{
    EVERY_N_MILLIS(300)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 1);
    }
    int complex_wave = matrixValues[0] + matrixValues[1];
    // int complex_wave =  vReal[5];
    complex_wave = constrain(map(complex_wave, 0, 32, 0, 255), 0, 255);
    stripe[(NUM_LEDS_STRIPE / 2)] = CHSV(complex_wave, 255, complex_wave);
    stripe[(NUM_LEDS_STRIPE / 2) - 1] = CHSV(complex_wave, 255, complex_wave);
    FOR_i(0, NUM_LEDS_STRIPE / 2)
    {
        stripe[i] = stripe[i + 1];
        stripe[NUM_LEDS_STRIPE - i] = stripe[(NUM_LEDS_STRIPE - i) - 1];
    }
}
int dotPos = 0;
bool left = false;
void PaletteDance()
{
    if (matrixValues[0] + matrixValues[1] > 20) // if (volume > avgVol) {
    {
        left = !left;
        for (int i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            float sinVal = abs(sin(
                (i + dotPos) *
                (PI / float(NUM_LEDS_STRIPE / 1.25))));
            sinVal *= sinVal;
            sinVal *= map(matrixValues[0] + matrixValues[1], 0, 32, 0, 255);
            CRGB col = ColorFromPalette(currentPaletteStripe, sinVal, 255, LINEARBLEND);
            stripe[i] = col;
        }
        dotPos += (left) ? -1 : 1;
    }
    else
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 5);
    }
    if (dotPos < 0)
        dotPos = NUM_LEDS_STRIPE - (NUM_LEDS_STRIPE / 6);
    else if (dotPos >= NUM_LEDS_STRIPE - NUM_LEDS_STRIPE / 6)
        dotPos = 0;
}
uint8_t gradient = 0;
uint8_t gradient2 = 0;
uint8_t gradient3 = 0;
float avgTime = 0;
float avgTime2 = 0;
float avgTime3 = 0;
float timeBump = 0;
float timeBump2 = 0;
float timeBump3 = 0;
int dotPos2 = 300;
int dotPos3 = 600;
bool left2 = false;
bool left3 = false;
void Snake()
{
    if (matrixValues[0] > 10)
    {

        avgTime = (((millis() / 1000.0) - timeBump) + avgTime) / 2.0;
        timeBump = millis() / 1000.0;

        // Change color a little on a bump
        gradient += 3;
        left ? gradient += 30 : gradient -= 30;
        // Change the direction the dot is going to create the illusion of "dancing."
        left = !left;
    }
    /*   if (matrixValues[3] + matrixValues[4] > 10)
       {

           avgTime2 = (((millis() / 1000.0) - timeBump2) + avgTime2) / 2.0;
           timeBump2 = millis() / 1000.0;

           // Change color a little on a bump
           gradient2 += 3;

           // Change the direction the dot is going to create the illusion of "dancing."
           left2 = !left2;
       }
       if (matrixValues[5] + matrixValues[6] + matrixValues[7] > 20)
       {
           avgTime3 = (((millis() / 1000.0) - timeBump3) + avgTime3) / 2.0;
           timeBump3 = millis() / 1000.0;

           // Change color a little on a bump
           gradient3 += 3;

           // Change the direction the dot is going to create the illusion of "dancing."
           left3 = !left3;
       }*/
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 10); // Leave a trail behind the dot.

    // uint32_t col = ColorPalette(-1); // Get the color at current "gradient."

    // The dot should only be moved if there's sound happening.
    //   Otherwise if noise starts and it's been moving, it'll appear to teleport.

    // Sets the dot to appropriate color and intensity
    for (int i = 0; i < 5; i++)
    {
        stripe[dotPos + i] = ColorFromPalette(currentPaletteStripe, gradient, map(matrixValues[0], 0, 16, 40, 255), LINEARBLEND);
    }

    // stripe[dotPos2] = ColorFromPalette(currentPaletteStripe, gradient2, map(matrixValues[4], 0, 16, 40, 255), LINEARBLEND);
    // stripe[dotPos3] = ColorFromPalette(currentPaletteStripe, gradient3, map(matrixValues[7], 0, 16, 40, 255), LINEARBLEND);
    // This is where "avgTime" comes into play.
    //   That variable is the "average" amount of time between each "bump" detected.
    //   So we can use that to determine how quickly the dot should move so it matches the tempo of the music.
    //   The dot moving at normal loop speed is pretty quick, so it's the max speed if avgTime < 0.15 seconds.
    //   Slowing it down causes the color to update, but only change position every other amount of loops.
    if (avgTime < 0.15)
    {
        dotPos += (left) ? -5 : 5;
    }
    else if (avgTime >= 0.15 && avgTime < 0.5 && gradient % 2 == 0)
    {
        dotPos += (left) ? -5 : 5;
    }
    else if (avgTime >= 0.5 && avgTime < 1.0 && gradient % 3 == 0)
    {
        dotPos += (left) ? -5 : 5;
    }
    else if (gradient % 4 == 0)
    {
        dotPos += (left) ? -5 : 5;
    }
    /*if (avgTime2 < 0.15)
    {

        dotPos2 += (left2) ? -1 : 1;
    }
    else if (avgTime2 >= 0.15 && avgTime2 < 0.5 && gradient2 % 2 == 0)
    {

        dotPos2 += (left2) ? -1 : 1;
    }
    else if (avgTime2 >= 0.5 && avgTime2 < 1.0 && gradient2 % 3 == 0)
    {

        dotPos2 += (left2) ? -1 : 1;
    }
    else if (gradient2 % 4 == 0)
    {

        dotPos2 += (left2) ? -1 : 1;
    }
    if (avgTime3 < 0.15)
    {

        dotPos3 += (left3) ? -1 : 1;
    }
    else if (avgTime3 >= 0.15 && avgTime3 < 0.5 && gradient3 % 2 == 0)
    {

        dotPos3 += (left3) ? -1 : 1;
    }
    else if (avgTime3 >= 0.5 && avgTime3 < 1.0 && gradient3 % 3 == 0)
    {

        dotPos3 += (left3) ? -1 : 1;
    }
    else if (gradient3 % 4 == 0)
    {

        dotPos3 += (left3) ? -1 : 1;
    }*/

    // Check if dot position is out of bounds.
    if (dotPos < 0)
        dotPos = NUM_LEDS_STRIPE - 1;
    else if (dotPos >= NUM_LEDS_STRIPE)
        dotPos = 0;

    /*if (dotPos2 < 0)
        dotPos2 = NUM_LEDS_STRIPE - 1;
    else if (dotPos2 >= NUM_LEDS_STRIPE)
        dotPos2 = 0;

    if (dotPos3 < 0)
        dotPos3 = NUM_LEDS_STRIPE - 1;
    else if (dotPos3 >= NUM_LEDS_STRIPE)
        dotPos3 = 0;*/
}
void audioLoop()
{

    // -- re-arrange FFT result to match with no. of columns on display ( xres )
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 2);
    FOR_i(0, NUM_LEDS_STRIPE / 2)
    {
        // data_avgs[i]=data_avgs[i]/2;
        int result = map(matrixValues[map(i, 0, 500, 0, 7)], 0, 16, 0, 255);
        // result = constrain(vImag[i],0,255);
        result = constrain(stripe[(NUM_LEDS_STRIPE / 2) - i].getLuma() + result, 0, 255);
        // stripe[(NUM_LEDS_STRIPE/2)+i]=constrain(stripe[(NUM_LEDS_STRIPE/2)-i].getLuma()+result,0,255);
        // data_avgs[i] = data_avgs[i]+result;
        stripe[(NUM_LEDS_STRIPE / 2) - i] = CHSV(beatsin8(30, 0, 255, 0, i), 255, result);
        stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(30, 0, 255, 0, i), 255, result);
    }
}
void meteorRain2()
{
    static int wave;
    EVERY_N_MILLIS(8000)
    {
        wave = random(10);
    }
    stripe[NUM_LEDS_STRIPE / 2].setHSV(beatsin8(wave), 255, 255);
    stripe[NUM_LEDS_STRIPE / 2 - 1].setHSV(beatsin8(wave), 255, 255);

    FOR_i(0, NUM_LEDS_STRIPE / 2)
    {
        stripe[i] = stripe[i + 1];
        stripe[i].r -= random(10);
        stripe[i].g -= random(10);
        stripe[i].b -= random(10);
        stripe[NUM_LEDS_STRIPE - i] = stripe[NUM_LEDS_STRIPE - i - 1];
        stripe[NUM_LEDS_STRIPE - i].r -= random(10);
        stripe[NUM_LEDS_STRIPE - i].g -= random(10);
        stripe[NUM_LEDS_STRIPE - i].b -= random(10);
    }

    FastLED.show();
    // FastLED.delay(SpeedDelay);
}
// настройки пламени
int HUE_GAP = 30;      // заброс по hue
#define FIRE_STEP 20   // шаг огня
int HUE_START = 0;     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define MIN_BRIGHT 00  // мин. яркость огня
#define MAX_BRIGHT 255 // макс. яркость огня
#define MIN_SAT 245    // мин. насыщенность
#define MAX_SAT 255    // макс. насыщенность
CHSV getFireColor(int val)
{
    // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
    return CHSV(
        HUE_START + map(val, 0, 255, 0, HUE_GAP),                   // H
        constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),      // S
        constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255) // V
    );
}
void fireTick()
{
    static uint32_t prevTime;
    HUE_START = 0;
    HUE_GAP = 30; // заброс по hue
    // двигаем пламя
    if (millis() - prevTime > 40)
    {
        prevTime = millis();
        FOR_i(0, NUM_LEDS_STRIPE)
        {
            stripe[i] = getFireColor((inoise8(i * FIRE_STEP, counter)));
        }
        counter += 20;
        FastLED.show();
    }
}

// Define variables used by the sequences.
uint8_t thisfade = 8;  // How quickly does it fade? Lower = slower fade rate.
int thishue = 50;      // Starting hue.
uint8_t thisinc = 1;   // Incremental value for rotating hues
uint8_t thissat = 100; // The saturation, where 255 = brilliant colours.
uint8_t thisbri = 255; // Brightness of a sequence. Remember, max_bright is the overall limiter.
int huediff = 256;     // Range of random #'s to use for hue
uint8_t thisdelay = 5; // We don't need much delay (if any)
void ChangeMe()
{                                                // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
    uint8_t secondHand = (millis() / 1000) % 15; // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
    static uint8_t lastSecond = 99;              // Static variable, means it's only defined once. This is our 'debounce' variable.
    if (lastSecond != secondHand)
    { // Debounce to make sure we're not repeating an assignment.
        lastSecond = secondHand;
        switch (secondHand)
        {
        case 0:
            thisinc = 1;
            thishue = 192;
            thissat = 255;
            thisfade = 2;
            huediff = 256;
            break; // You can change values here, one at a time , or altogether.
        case 5:
            thisinc = 2;
            thishue = 128;
            thisfade = 8;
            huediff = 64;
            break;
        case 10:
            thisinc = 1;
            thishue = random16(255);
            thisfade = 1;
            huediff = 16;
            break; // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
        case 15:
            break; // Here's the matching 15 for the other one.
        }
    }
} // ChangeMe()
int new_star;
void effect1()
{
    new_star++;
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 8);
    if (new_star > 1)
    {
        stripe[random(NUM_LEDS_STRIPE)] = CRGB::White;
        new_star = 0;
    }

    FastLED.delay(30);
    FastLED.show();
}
int result_vu2;
void VU_meter()
{
#define chanel 27

    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 100);
    int input_vu2 = constrain(map(vReal[chanel], 0, NUM_LEDS_STRIPE / 2, 0, NUM_LEDS_STRIPE / 2), 0, NUM_LEDS_STRIPE / 2);
    if (result_vu2 < input_vu2)
    {
        result_vu2 = result_vu2 + ((input_vu2 - result_vu2) * .3); //((map(vReal[chanel],0,512,0,NUM_LEDS_STRIPE/2)-result_vu)/2);
    }
    else
    {
        result_vu2 = result_vu2 - ((result_vu2 - input_vu2) * .3); //((map(vReal[chanel],0,512,0,NUM_LEDS_STRIPE/2)-result_vu)/2);
    }
    FOR_i(0, NUM_LEDS_STRIPE)
    {
        if (result_vu2 > i)
        {
            stripe[(NUM_LEDS_STRIPE / 2) - i] = ColorFromPalette(currentPaletteStripe, map(result_vu2, 0, 255, 0, i), 255, LINEARBLEND);

            stripe[(NUM_LEDS_STRIPE / 2) + i] = ColorFromPalette(currentPaletteStripe, map(result_vu2, 0, 255, 0, i), 255, LINEARBLEND);
        }
        else
        {
            // stripe[(NUM_LEDS_STRIPE / 2) + i + 1] = stripe[(NUM_LEDS_STRIPE / 2) + i];
            // stripe[(NUM_LEDS_STRIPE / 2) - i - 1] = stripe[(NUM_LEDS_STRIPE / 2) - i];
            //  stripe[(NUM_LEDS_STRIPE / 2) - i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
            //   stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
        }
    }
    FastLED.show();
}
CRGBArray<NUM_LEDS_STRIPE> leds;
void spectrumWaves2()
{
    // readAudio();
    // fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 2);
    int centerLed = NUM_LEDS_STRIPE / 2;
    CRGB color = CRGB(matrixValues[5] / 8, matrixValues[6], matrixValues[1] / 2);

    stripe[centerLed] = color;
    stripe[centerLed].fadeToBlackBy(matrixValues[3] / 12);

    stripe[centerLed - 1] = color;
    stripe[centerLed - 1].fadeToBlackBy(matrixValues[3] / 12);

    // move to the left
    for (int i = NUM_LEDS_STRIPE - 1; i > centerLed / 2; i--)
    {
        stripe[i] = stripe[i - 1];
        stripe[centerLed + i] = stripe[centerLed + i - 1];
    }
    // move to the right
    for (int i = 0; i < centerLed / 2; i++)
    {
        stripe[i] = stripe[i + 1];
        stripe[centerLed + i] = stripe[centerLed + i + 1];
    }
}
void dot_beat()
{
    CHSV colorix = CHSV(255, 255, map(matrixValues[0], 0, 16, 50, 255));
    uint8_t bpm = 5;
    uint16_t inner = beatsin16(bpm, NUM_LEDS_STRIPE / 4, NUM_LEDS_STRIPE / 4 * 3);  // Move 1/4 to 3/4
    uint16_t outer = beatsin16(bpm, 5, NUM_LEDS_STRIPE - (bpm * 2));                // Move entire length
    uint16_t middle = beatsin16(bpm, NUM_LEDS_STRIPE / 3, NUM_LEDS_STRIPE / 3 * 2); // Move 1/3 to 2/3

    stripe[middle] = CRGB::Yellow;
    stripe[inner] = CRGB::Blue;
    for (uint8_t i = 0; i < (bpm * 2); i++)
    {
        stripe[outer + i] = colorix;
    }

    stripe[outer] = colorix;

    nscale8(stripe, NUM_LEDS_STRIPE, 200); // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);
}
void beatWave()
{

    uint8_t wave1 = beatsin8(9, 0, 255); // That's the same as beatsin8(9);
    uint8_t wave2 = beatsin8(8, 0, 255);
    uint8_t wave3 = beatsin8(7, 0, 255);
    uint8_t wave4 = beatsin8(6, 0, 255);

    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    { // make from the map and array int[lednumber]=realposition
        stripe[i] = ColorFromPalette(ForestColors_p, i + wave1 + wave2 + wave3 + wave4, 255, LINEARBLEND);
        //    leds[t.first].fadeLightBy( dbrightness );
    }

} // beatWave()
uint8_t wave1 = 0; // That's the same as 9);
uint8_t wave2 = 0;
uint8_t wave3 = 0;
uint8_t wave4 = 0;
void test()
{

    wave1 += matrixValues[0]; // That's the same as 9);
    wave2 += matrixValues[2];
    wave3 += matrixValues[4];
    wave4 += matrixValues[6];

    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    { // make from the map and array int[lednumber]=realposition
        stripe[i] = ColorFromPalette(currentPaletteStripe, i + wave1 + wave2 + wave3 + wave4, 255, LINEARBLEND);
        //    leds[t.first].fadeLightBy( dbrightness );
    }
}
void audioSparkleTreb3()
{
    fadeToBlackBy(leds, NUM_LEDS_STRIPE, 128);
    float specCombo = (matrixValues[5] + matrixValues[6]) / 2.0;
    for (int i = 0; i < specCombo / 50; i++)
    {
        leds[random16(NUM_LEDS_STRIPE)] = ColorFromPalette(currentPaletteStripe, random8(255), 255, LINEARBLEND);
    }
} // audioSparkleTreb3()
boolean beat()
{
    int beatDelay = 500;
    bool isBeat = false;
    for (int i = 0; i < 7; i++)
    {
        if (matrixValues[i] >= 5)
        {
            isBeat = true;
        }
    }
    if (isBeat)
    {
        EVERY_N_MILLIS(beatDelay)
        {
            // Serial.println("BEAT");
            return true;
        }
    }
    else
    {
        return false;
    }
    return false;
}
void CometKITT(byte baseHueColor = 0, byte commetSpeed = 32, byte fadeSpeed = 128, byte colorSpeed = 64)
{
    int cometSize = 15;
    // fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 128);
    for (int j = 0; j < NUM_LEDS_STRIPE; j++)
    {
        if (random(10) > 6)
        {
            stripe[j].fadeToBlackBy(fadeSpeed);
        }
    }
    EVERY_N_MILLISECONDS(50)
    {
        // fadeToBlackBy(leds, NUM_LEDS, fadeSpeed);

        int iPos = beatsin16(((stripeValues[7] / 10) + (stripeValues[1] / 10)) / 2, 0, NUM_LEDS_STRIPE - cometSize);
        byte hue = beatsin8(map(stripeValues[3], 0, 75, 2, 10));
        for (int i = iPos; i < iPos + cometSize; i++)
            stripe[i] = CHSV(hue, 255, map(stripeValues[0], 0, 75, 100, 255));

        int iPos2 = beatsin16(((stripeValues[0] / 10) + (stripeValues[6] / 10)) / 2, 0, NUM_LEDS_STRIPE - cometSize);
        byte hue2 = beatsin8(map(stripeValues[4], 0, 75, 2, 10));
        for (int i = iPos2; i < iPos2 + cometSize; i++)
            stripe[i] = CHSV(hue2, 255, map(stripeValues[7], 0, 75, 100, 255));
        // FastLED.show();
    }
}
void justKITTTT()
{
    CometKITT();
}

int iasdf;
int ghjkl = NUM_LEDS_STRIPE;
void meteorRain()
{
    CRGB color = ColorFromPalette(currentPaletteStripe, colorHueStripe, 255);

    for (int j = 0; j < NUM_LEDS_STRIPE; j++)
    {
        if (random(10) > 2)
        {
            stripe[j] = fadeTowardColor(stripe[j], CRGB::Black, 30);
        }
        if (random(10) > 3)
        {
            stripe[j + 1] = fadeTowardColor(stripe[j], CRGB::Black, 30);
        }
    }

    // draw meteor
    for (int j = 0; j < 20; j++)
    {
        if ((iasdf - j < NUM_LEDS_STRIPE / 2) && (iasdf - j >= 0))
        {
            stripe[iasdf - j] = color;
            stripe[iasdf - j + 1] = color;
        }
    }
    for (int j = 0; j < 20; j++)
    {
        if ((ghjkl - j > NUM_LEDS_STRIPE / 2) && (ghjkl - j >= 0))
        {
            stripe[ghjkl - j] = color;
            stripe[ghjkl - j + 1] = color;
        }
    }
    ghjkl <= NUM_LEDS_STRIPE / 2 ? ghjkl = NUM_LEDS_STRIPE : ghjkl -= 10;
    iasdf >= NUM_LEDS_STRIPE / 2 ? iasdf = 0 : iasdf += 10;
    FastLED.show();
}
bool swap;
struct meteor
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

        brightness = scale8(brightness, fade); // Adjust brightness accordingly to strip length

        if (pos >= NUM_LEDS_STRIPE)
            exist = false; // Kill it once it's expired.
        if (pos <= 0)
            exist = false; // Kill it once it's expired.

    } // Move()

    void Init(uint8_t Fade, uint8_t MaxLife)
    { // Typically 216, 20

        pos = random16(NUM_LEDS_STRIPE / 20, NUM_LEDS_STRIPE - NUM_LEDS_STRIPE / 20); // Avoid spawning too close to edge.
        if (swap)
        {
            velocity = 1;
            swap = false;
        }
        else
        {
            velocity = -1;
            swap = true;
        }

        // random(2) == 1 ? velocity = 2 : velocity = -2; // -1 or 1
        life = 0;         // 0 to Maxlife                                                               // 10 called
        exist = true;     // 0, 1
        brightness = 255; // 0 to 255
        color = millis(); // hue;
        fade = Fade;      // 192 called
    }
};
typedef struct meteor Meteor;
#define meteorsAmount (NUM_LEDS_STRIPE / 10)
Meteor meteors[meteorsAmount];
void meteorBeatDetector()
{
    if (beat())
    {

        for (int i = 0; i < meteorsAmount; i++)
        { // Check to see if ripple has expired, and if so, create a new one.
            if (random8() > 200 && !meteors[i].exist)
            {                             // Randomly create a new ripple if this one has expired.
                meteors[i].Init(232, 20); // Initialize the ripple array with Fade and MaxLife values.
            }
        }
    }
    EVERY_N_MILLIS(100)
    {
        for (int i = 0; i < 20; i++)
        { // Move the ripple if it exists
            if (meteors[i].exist)
            {

                stripe[meteors[i].pos] = ColorFromPalette(currentPaletteStripe, meteors[i].color, map(matrixValues[0], 0, 16, 25, 255), LINEARBLEND);
                meteors[i].Move();
            }
        }
    }

    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 20);
}

void analyzerColumns()
{
    fill_solid(stripe, NUM_LEDS_STRIPE, CRGB::Black);

    const uint8_t columnSize = NUM_LEDS_STRIPE / 7;

    for (uint8_t i = 0; i < 7; i++)
    {
        uint8_t columnStart = i * columnSize;
        uint8_t columnEnd = columnStart + columnSize;

        if (columnEnd >= NUM_LEDS_STRIPE)
            columnEnd = NUM_LEDS_STRIPE - 1;

        uint8_t columnHeight = map8(stripeValues[i], 1, columnSize);

        for (uint8_t j = columnStart; j < columnStart + columnHeight; j++)
        {
            if (j >= NUM_LEDS_STRIPE || j >= columnEnd)
                continue;

            stripe[j] = CHSV(i * 40, 255, 255);
        }
    }
}
void modeShooting()
{

    int speed = (matrixValues[0] / 2) + 1;
    for (int i = NUM_LEDS_STRIPE - 1; i > 0; i--)
    {
        stripe[i] = stripe[i - speed];
    }

    if (matrixValues[0] > 8)
    {
        for (int i = 0; i < speed; i++)
        {
            stripe[i] = CHSV((speed) + colorHueStripe + random(50), 255, 255);
        }
    }
    else
    {
        for (int i = 0; i < speed; i++)
        {
            stripe[i] = ColorFromPalette(currentPaletteStripe, i * 3, 50, NOBLEND);
        }
    }
}

void randomPosBeat()
{
    int eight = NUM_LEDS_STRIPE / 8;
    // And and end point.
    for (int i = 0; i < NUM_BANDS; i++)
    {
        int pos = random(8);
        int strt = random16(eight * pos, eight * pos + eight);  // Start of FastLED stuff. Get a starting point.
        int end = map(matrixValues[i], 0, 16, 0, eight) + strt; // End of FastLED stuff. Get an ending point.

        for (int j = strt; j < end; j++)
        {

            stripe[j] = CHSV(i * 30, 255, 255);
        }
    }

    /* if (matrixValues[0] + matrixValues[1] > 20)
     {

         for (int i = strt; i < ende; i++)
         {
            // uint8_t index = inoise8(i * 30, millis() + i * 30);                          // Make Perlin noise beteween those points.
          //   stripe[i] = ColorFromPalette(currentPaletteStripe, index, 255, LINEARBLEND); // And display it with palettes.
         }
     }*/

    EVERY_N_MILLIS(50)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 64); // Fade the LED's
                                                    // FastLED.show();                             // We can't show too often, or things break.
    }
}
bool initBalls = false;
void Balls()
{
    if (!initBalls)
    {
        for (int i = 0; i < NUM_BALLS; i++)
        { // Initialize variables
            tLast[i] = millis();
            h[i] = h0;
            pos[i] = 0;            // Balls start on the ground
            vImpact[i] = vImpact0; // And "pop" up at vImpact0
            tCycle[i] = 0;
            COR[i] = 0.90 - float(i) / pow(NUM_BALLS, 2);
        }
        initBalls = true;
    }
    for (int i = 0; i < NUM_BALLS; i++)
    {
        stripe[pos[i]] = CRGB::Black;
    }
    for (int i = 0; i < NUM_BALLS; i++)
    {
        tCycle[i] = millis() - tLast[i]; // Calculate the time since the last time the ball was on the ground

        // A little kinematics equation calculates positon as a function of time, acceleration (gravity) and intial velocity
        h[i] = 0.5 * GRAVITY * pow(tCycle[i] / 1000, 2.0) + vImpact[i] * tCycle[i] / 1000;

        if (h[i] < 0)
        {
            h[i] = 0;                         // If the ball crossed the threshold of the "ground," put it back on the ground
            vImpact[i] = COR[i] * vImpact[i]; // and recalculate its new upward velocity as it's old velocity * COR
            tLast[i] = millis();

            if (vImpact[i] < 0.01)
                vImpact[i] = vImpact0; // If the ball is barely moving, "pop" it back up at vImpact0
        }

        pos[i] = round(h[i] * (NUM_LEDS_STRIPE - 1) / h0); // Map "h" to a "pos" integer index position on the LED strip
    }

    // Choose color of LEDs, then the "pos" LED on
    for (int i = 0; i < NUM_BALLS; i++)
        stripe[pos[i]] = CHSV(uint8_t(i * 40), 255, 255);
    // FastLED.show();
    //  Then off for the next loop around
}
int wrap(int steper)
{
    if (steper < 0)
        return NUM_LEDS_STRIPE + steper;
    if (steper > NUM_LEDS_STRIPE - 1)
        return steper - NUM_LEDS_STRIPE;
    return steper;
}
void ripple()
{

    if (currentBg == nextBg)
    {
        nextBg = random(256);
    }
    else if (nextBg > currentBg)
    {
        currentBg++;
    }
    else
    {
        currentBg--;
    }
    for (uint16_t l = 0; l < NUM_LEDS_STRIPE; l++)
    {
        stripe[l] = CHSV(currentBg, 255, 50); // strip.setPixelColor(l, Wheel(currentBg, 0.1));
    }

    if (steper == -1)
    {
        center = random(NUM_LEDS_STRIPE);
        color = random(256);
        steper = 0;
    }

    if (steper == 0)
    {
        stripe[center] = CHSV(color, 255, 255); // strip.setPixelColor(center, Wheel(color, 1));
        steper++;
    }
    else
    {
        if (steper < maxSteps)
        {
            // Serial.println(pow(fadeRate, steper));

            stripe[wrap(center + steper)] = CHSV(color, 255, pow(fadeRate, steper) * 255); //   strip.setPixelColor(wrap(center + steper), Wheel(color, pow(fadeRate, steper)));
            stripe[wrap(center - steper)] = CHSV(color, 255, pow(fadeRate, steper) * 255); //   strip.setPixelColor(wrap(center - steper), Wheel(color, pow(fadeRate, steper)));
            if (steper > 3)
            {
                stripe[wrap(center + steper - 3)] = CHSV(color, 255, pow(fadeRate, steper - 2) * 255); //   strip.setPixelColor(wrap(center + steper - 3), Wheel(color, pow(fadeRate, steper - 2)));
                stripe[wrap(center - steper + 3)] = CHSV(color, 255, pow(fadeRate, steper - 2) * 255); //   strip.setPixelColor(wrap(center - step + 3), Wheel(color, pow(fadeRate, step - 2)));
            }
            steper++;
        }
        else
        {
            steper = -1;
        }
    }

    minimumDelayFromPatternsStripe(50);
}
int secondHand;
void matrixxx()
{ // One line matrix
  // Serial.println(secondHand);
    if (huerots)
        thishues = thishues + 5;

    if (random16(50) > 35 - matrixValues[0] + matrixValues[7])
    {
        if (thisdirs == 0)
            stripe[0] = CHSV(thishues + colorHueStripe, thissats, 255);
        else
            stripe[NUM_LEDS_STRIPE - 1] = CHSV(thishues + colorHueStripe, thissats, 255);
    }
    else
    {
        stripe[0] = CHSV(thishues, thissats, 0);
    }

    if (thisdirs == 0)
    {

        for (int i = NUM_LEDS_STRIPE - 1; i > 0; i--)
            stripe[i] = stripe[i - 1];
    }
    else
    {

        for (int i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            stripe[i] = stripe[i + 1];
        }
    }
} // matrix()

void ChangeMeone()
{                                                       // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
                                                        // ll
    secondHand == 2000 ? secondHand = 0 : secondHand++; // Change '25' to a different value to change length of the loop.
                                                        // Static variable, means it's only defined once. This is our 'debounce' variable.

    if (secondHand == 0)
    {
        thisdelays = 30;
        thishues = colorHueStripe;
        huerots = 0;
        thisdirs = thisdirs == 1 ? 0 : 1;
    }
    if (secondHand == 1000)
    {
        thisdelays = 130;
        thishues = millis() / 10000 / secondHand;
        huerots = 10;
        thisdirs = thisdirs == 1 ? 0 : 1;
    }
} // ChangeMe()
void matrixone()
{
    ChangeMeone();
    matrixxx();
    // show_at_max_brightness_for_power();
    minimumDelayFromPatternsStripe(thisdelay * 2.5);
    //   Serial.println(LEDS.getFPS());
} // loop()

int ar = 0;
void around()
{
    // fill_solid(stripe, NUM_LEDS_STRIPE, CRGB::Black);
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 1);
    for (uint8_t i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        if (random8() > 170)
        {
            stripe[i].nscale8(50);
        }
    }

    if (ar >= NUM_LEDS_STRIPE + 1)
    {
        ar = 1;
    }
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < matrixValues[j] / 2 + 1; i++)
        {
            stripe[wrap(ar + i + j * (NUM_LEDS_STRIPE / 8))] = CHSV(j * 32, 255, 255);
        }
    }

    EVERY_N_MILLIS(1) { ar++; }
}
//{function,"name", isAudioReactive }
const PatternAndNameList patternsStripe = {

    {audioLoop, "audioLoop", true},
    {Snake, "Snake", true},
    {PaletteDance, "PaletteDance", true},
    {water_fall_vu, "Waterfall", true},
    {spectrumDetector, "spectrumDetector", true},
    {beatDetector, "beatDetector", true},
    {dot_beat, "dot_beat", true},
    {around, "Around", true},
    {randomPosBeat, "randomPosBeat", true},
    {modeShooting, "modeShooting", true},
    {analyzerColumns, "analyzerColumns", true},
    {meteorBeatDetector, "meteorBeatDetector", true},

    // {spectrumWaves2, "spectrumWaves2" , true},// making panic guru
    {VU_meter, "vu_meter", true},
    {test, "test", false},
    {beatWave, "beatWave", false},
    {fireTick, "fireTick", false},
    {meteorRain2, "meteorRain2", false},
    {meteorRain, "meteorRain", false},
    {twinkleFox, "TwinkleFox", false},
    {heatMapShow, "Heatmap", false},
    {matrixone, "Matrix One", false},
    {ripple, "Ripple", false},
    {Balls, "Balls", false},
    {justKITTTT, "CometKITT", false},
    {colorWipe, "colorWipe", false},
    {pacifica_loop, "Pacifica", false},
    {rainbow, "Rainbow", false},
    {rippless, "Ripple", false},
    {theaterChase, "Theater-Chase", false},
    {bpmStripe, "BPM-Stripe", false},
    //{displayUpdateStripe, "Display_Update_Stripe", false},
    {sinelon, "Sinelon", false},
    {juggle, "Juggle", false},
    {strobo, "Strobo", false},
    {confetti, "Confetti", false},
    {rainbowWithGlitter, "Rainbow-With-Glitter", false},
    {stripeVuBandsSolidColor, "SolidColorSpectrum", true},
    {stripeVuBandsColors, "Color-bands-Spectrum", true},
    {stripeVuBandsBeatsin, "Beatsin-Spectrum", true},
};

const uint8_t StripePatternsAmount = ARRAY_SIZE(patternsStripe) - 1;