

#pragma once

#include "Imports.h"

/*uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;
int colorripple;
int center = 0;
int step = -1;
int maxSteps = 30;
float fadeRate = 3.80;
int diff;
uint32_t currentBg2 = random(256);
uint32_t nextBg2 = currentBg2;
int colorripple2;
int center2 = 0;
int step2 = -1;
int maxSteps2 = 30;
float fadeRate2 = 3.20;
int diff2;
#define NUM_LEDS 90
void ripple()
{
    if (millis() - previousMillis > patternInterval)
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
        for (uint16_t l = 0; l < NUM_LEDS; l++)
        {
            SetRightStripe(l] = CRGB(currentBg, 0.1));
        }

        if (step == -1)
        {
            center = random(NUM_LEDS);
            colorripple = random(256);
            step = 0;
        }

        if (step == 0)
        {
            SetRightStripe(center] = CRGB(colorripple, 1));
            step++;
        }
        else
        {
            if (step < maxSteps)
            {
                //  Serial.println(pow(fadeRate, step));

                SetRightStripe(wrap(center + step)] = CRGB(colorripple, pow(fadeRate, step)));
                SetRightStripe(wrap(center - step)] = CRGB(colorripple, pow(fadeRate, step)));
                if (step > 3)
                {
                    SetRightStripe(wrap(center + step - 3)] = CRGB(colorripple, pow(fadeRate, step - 2)));
                    SetRightStripe(wrap(center - step + 3)] = CRGB(colorripple, pow(fadeRate, step - 2)));
                }
                step++;
            }
            else
            {
                step = -1;
            }
        }
        if (currentBg2 == nextBg2)
        {
            nextBg2 = random(256);
        }
        else if (nextBg2 > currentBg2)
        {
            currentBg2++;
        }
        else
        {
            currentBg2--;
        }
        for (uint16_t l = 0; l < NUM_LEDS; l++)
        {
            SetLeftStripe(l] = CRGB(currentBg2, 0.1));
        }

        if (step2 == -1)
        {
            center2 = random(NUM_LEDS);
            colorripple2 = random(256);
            step2 = 0;
        }

        if (step2 == 0)
        {
            SetLeftStripe(center2] = CRGB(colorripple2, 1));
            step2++;
        }
        else
        {
            if (step2 < maxSteps2)
            {
                //  Serial.println(pow(fadeRate, step));

                SetLeftStripe(wrap(center2 + step2)] = CRGB(colorripple2, pow(fadeRate2, step2)));
                SetLeftStripe(wrap(center2 - step2)] = CRGB(colorripple2, pow(fadeRate2, step2)));
                if (step > 3)
                {
                    SetLeftStripe(wrap(center2 + step2 - 3)] = CRGB(colorripple2, pow(fadeRate2, step2 - 2)));
                    SetLeftStripe(wrap(center2 - step2 + 3)] = CRGB(colorripple2, pow(fadeRate2, step2 - 2)));
                }
                step2++;
            }
            else
            {
                step2 = -1;
            }
        }
        FastLED.show();
        previousMillis = millis();
    }
}
int wrap(int step)
{
    if (step < 0)
        return NUM_LEDS + step;
    if (step > NUM_LEDS - 1)
        return step - NUM_LEDS;
    return step;
}
int wrap2(int step)
{
    if (step2 < 0)
        return NUM_LEDS + step2;
    if (step2 > NUM_LEDS - 1)
        return step2 - NUM_LEDS;
    return step2;
}*/