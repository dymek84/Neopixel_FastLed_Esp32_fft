
#pragma once

#include "Imports.h"

void VUStripe()
{
    analyzeAudio();
    int signalAvg = audioSample();
    EVERY_N_MILLISECONDS(5)
    {
        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 60); // Fade out pixels.
    }
    uint16_t pos = beat8(signalAvg) % NUM_LEDS_STRIPE; // modulo the position to be within NUM_LEDS
    stripe[pos] = CHSV(colorTimer, 200, 255);
}

void displayUpdateStripe()
{
    analyzeAudio();
    uint16_t color;

    for (int i = 0; i < NUM_BANDS; i++)
    {
        color += 255 / NUM_BANDS;
        for (int j = NUM_BANDS * i; j < NUM_BANDS * i + 50; j++)
        {
            // Serial.println(bandValues[i]);
            if (j <= (map(bandValues[i], 0, 255, 0, 50) + NUM_BANDS * i))
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
void stripeVuBandsSolidColor()
{
    analyzeAudio();
    for (uint8_t x = 0; x < 8; x++)
    {
        for (int i = 0; i < 75; i++)
        {
            int on = 75 + x * 150;
            if (i < bandValues[x])
            {
                stripe[on + i] = CHSV(32 * x, 255, 255);
                stripe[on - i] = CHSV(32 * x, 255, 255);
            }
            else
            {
                stripe[on + i] = CHSV(0, 0, 0);
                stripe[on - i] = CHSV(0, 0, 0);
            }
        }
    }
}
void stripeVuBandsBeatsin()
{
    analyzeAudio();

    // fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 125); // Fade out pixels.
    for (uint8_t x = 0; x < 8; x++)
    {
        for (int i = 0; i < 75; i++)
        {
            int on = 75 + x * 150;
            input_vu[x] = bandValues[x];
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
    analyzeAudio();
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 125); // Fade out pixels.
    for (uint8_t x = 0; x < 8; x++)
    {
        for (int i = 0; i < 75; i++)
        {
            int on = 75 + x * 150;

            if (i < bandValues[x])
            {
                stripe[on + i] = CHSV(colorTimer + (x * 32), 255, BRIGHTNESS);
                stripe[on - i] = CHSV(colorTimer + (x * 32), 255, BRIGHTNESS);
            }
            else
            {
                // stripe[on - i] = CHSV(colorTimer + (x * 32), 255, 0);
                // stripe[on + i] = CHSV(colorTimer + (x * 32), 255, 0);
            }
            /*  if (i < bandValues[1])
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
    analyzeAudio();
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
        j = bandValues[i]; // take the pink noise average level out, take the asbolute value to avoid negative numbers
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
