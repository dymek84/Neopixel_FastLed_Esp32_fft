
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

void colorWipe()
{

    //  Update delay time
    stripe[pixelCurrent] = CHSV(colorTimer, 255, 255); //  Set pixel's color (in RAM)
    FastLED.show();                                    //  Update strip to match
    pixelCurrent + 15;                                 //  Advance current pixel
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
    stripe[pos2] += CHSV(colorTimer + random8(64), 200, 255);
}

void rainbow()
{
    fill_rainbow(stripe, NUM_LEDS_STRIPE, colorTimer, 7);
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
    heatMap(currentPalette, true);
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
CRGB led_bucket[NUM_LEDS_STRIPE];
int s = 0;
void bucketVU()
{
    int halfStripe = NUM_LEDS_STRIPE / 2;
    //  processAudio();
    s = stripeValues[0];
    s = s * 10;
    //  Serial.println(s);
    //  delay(50);

    led_bucket[600] = CHSV(map(stripeValues[2], 0, 75, 0, 255), 255, map(stripeValues[0], 0, 75, 0, 255));
    led_bucket[601] = CHSV(map(stripeValues[2], 0, 75, 0, 255), 255, map(stripeValues[0], 0, 75, 0, 255));

    for (int i = 0; i <= (NUM_LEDS_STRIPE - 2); i++)
    {
        //   led_bucket[NUM_LEDS_STRIPE - 1 - i] = led_bucket[(NUM_LEDS_STRIPE)-i - 2];
        //   stripe[NUM_LEDS_STRIPE - 1 - i] = led_bucket[(NUM_LEDS_STRIPE)-i - 2];
        led_bucket[NUM_LEDS_STRIPE - 1 - i] = led_bucket[(NUM_LEDS_STRIPE)-i - 2];
        stripe[NUM_LEDS_STRIPE - i] = led_bucket[(NUM_LEDS_STRIPE)-i - 2];
        stripe[i] = led_bucket[(NUM_LEDS_STRIPE)-i - 2];
        stripe[(NUM_LEDS_STRIPE - 1) - i] = led_bucket[NUM_LEDS_STRIPE - 1 - i];
    }
    if (s >= 450)
    {
        s = 450;
    }
    if (s <= 100)
    {
        s = 100;
    }
    for (int i = (450 - s) / 15; i >= 0; i--)
    {
        // stripe[ i] = CRGB(0, 0, 0);
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
                stripe[on + i] = CHSV(colorTimer + (x * 32), 255, BRIGHTNESS);
                stripe[on - i] = CHSV(colorTimer + (x * 32), 255, BRIGHTNESS);
            }
            else
            {
                // stripe[on - i] = CHSV(colorTimer + (x * 32), 255, 0);
                // stripe[on + i] = CHSV(colorTimer + (x * 32), 255, 0);
            }
            /*  if (i < stripeValues[1])
              {
                  stripe[225 + i] = CHSV(colorTimer + 25, 255, BRIGHTNESS);
                  stripe[225 - i] = CHSV(colorTimer + 25, 255, BRIGHTNESS);
              }
              else
              {
                  stripe[225 - i] = CHSV(colorTimer + 25, 255, 0);
                  stripe[225 + i] = CHSV(colorTimer + 25, 255, 0);
              }*/
        }
    }
}
float noise_fact[] = {15, 7, 1.5, 1, 1.2, 1.4, 1.7, 3};     // noise level determined by playing pink noise and seeing levels [trial and error]{204,188,68,73,150,98,88,68}
float noise_fact_adj[] = {15, 7, 1.5, 1, 1.2, 1.4, 1.7, 3}; // noise level determined by playing pink noise and seeing levels [trial and error]{204,188,68,73,150,98,88,68}
int counter2 = 0;
void runningVU()
{
    // processAudio();
    int prev_j[8];
    int beat = 0;
    int prev_oct_j;
    int counter = 0;
    int prev_beat = 0;
    int led_index = 0;
    int saturation = 0;
    int saturation_prev = 0;
    int brightness = 0;
    int brightness_prev = 0;
    for (int i = 1; i < 8; i++)
    { // goes through each octave. skip the first 1, which is not useful

        int j;
        j = stripeValues[i]; // take the pink noise average level out, take the asbolute value to avoid negative numbers
        if (j < 10)
        {
            j = 0;
        }
        j = j * noise_fact_adj[i];

        if (j < 10)
        {
            j = 0;
        }
        else
        {
            j = j * noise_fact_adj[i];
            if (j > 180)
            {
                if (i >= 7)
                {
                    beat += 2;
                }
                else
                {
                    beat += 1;
                }
            }
            j = j / 30;
            j = j * 30; // (force it to more discrete values)
        }

        prev_j[i] = j;

        //     Serial.print(j);
        //     Serial.print(" ");

        // this fills in 11 LED's with interpolated values between each of the 8 OCT values
        if (i >= 2)
        {
            led_index = 2 * i - 3;
            prev_oct_j = (j + prev_j[i - 1]) / 2;

            saturation = constrain(j + 30, 0, 255);
            saturation_prev = constrain(prev_oct_j + 30, 0, 255);
            brightness = constrain(j, 0, 255);
            brightness_prev = constrain(prev_oct_j, 0, 255);
            if (brightness == 255)
            {
                saturation = 50;
                brightness = 200;
            }
            if (brightness_prev == 255)
            {
                saturation_prev = 50;
                brightness_prev = 200;
            }

            for (uint8_t y = 0; y < 5; y++)
            {
                stripe[XY(led_index - 1, y)] = CHSV(j + y * 30, saturation, brightness);
                if (i > 2)
                {
                    prev_oct_j = (j + prev_j[i - 1]) / 2;
                    stripe[XY(led_index - 2, y)] = CHSV(prev_oct_j + y * 30, saturation_prev, brightness_prev);
                }
            }
        }
    }

    if (beat >= 7)
    {
        fill_solid(stripe, NUM_LEDS_STRIPE, CRGB::Gray);
        FastLED.setBrightness(120);

        //    FastLED.setBrightness(200);
    }
    else
    {
        if (prev_beat != beat)
        {
            FastLED.setBrightness(40 + beat * beat * 5);
            prev_beat = beat;
        }
    }

    FastLED.show();
    if (beat)
    {
        counter2 += ((beat + 4) / 2 - 2);
        if (counter2 < 0)
        {
            counter2 = 1000;
        }
        if (beat > 3 && beat < 7)
        {
            FastLED.delay(20);
        }
        beat = 0;
    }

    // Serial.println();
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
int i;
void meteorRain()
{
    CRGB color = ColorFromPalette(currentPalette, colorTimer, 255);

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
        if ((i - j < NUM_LEDS_STRIPE) && (i - j >= 0))
        {
            stripe[i - j] = color;
            stripe[i - j + 1] = color;
        }
    }

    i >= NUM_LEDS_STRIPE ? i = 0 : i += 15;
    FastLED.show();
}

void beatDetector()
{
    if (matrixValues[0] + matrixValues[1] > 20)
    {
        int strt = random16(NUM_LEDS_STRIPE / 2);        // Start of FastLED stuff. Get a starting point.
        int ende = strt + random16(NUM_LEDS_STRIPE / 2); // And and end point.
        for (int i = strt; i < ende; i++)
        {
            uint8_t index = inoise8(i * 30, millis() + i * 30);                    // Make Perlin noise beteween those points.
            stripe[i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND); // And display it with palettes.
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
                stripe[i + x * 61] = ColorFromPalette(currentPalette, x * 32, 255, LINEARBLEND);
                stripe[NUM_LEDS_STRIPE - (i + x * 61)] = ColorFromPalette(currentPalette, x * 32, 255, LINEARBLEND); // And display it with palettes.
            }
        }
    }
    EVERY_N_MILLIS(50)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 64); // Fade the LED's
                                                    // FastLED.show();                             // We can't show too often, or things break.
    }
}
const PatternAndNameList patternsStripe = {
    {spectrumDetector, "spectrumDetector"},
    {beatDetector, "beatDetector"},
    {meteorRain, "meteorRain"},
    {twinkleFox, "TwinkleFox"},
    {bucketVU, "BucketSpectrum"},
    {heatMapShow, "Heatmap"},
    {stripeVuBandsSolidColor, "SolidColorSpectrum"},
    {stripeVuBandsColors, "Color-bands-Spectrum"},
    {stripeVuBandsBeatsin, "Beatsin-Spectrum"},
    {colorWipe, "colorWipe"},
    {pacifica_loop, "Pacifica"},
    {rainbow, "Rainbow"},
    {rippless, "Ripple"},
    {salut, "Salut"},
    {theaterChase, "Theater-Chase"},
    {bpmStripe, "BPM-Stripe"},
    {displayUpdateStripe, "Display_Update_Stripe"},
    {sinelon, "Sinelon"},
    {juggle, "Juggle"},
    {strobo, "Strobo"},
    {confetti, "Confetti"},
    {rainbowWithGlitter, "Rainbow-With-Glitter"}};

const uint8_t StripePatternsAmount = ARRAY_SIZE(patternsStripe) - 1;