

#pragma once

#include "Imports.h"

uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;
int colorripple;
int center = 0;
int step = -1;
int mapFade = map(userColor, 0, 255, 1, 9);
float fadeRate = mapFade * 0.1;
int maxSteps = halfofPixels * fadeRate;

int diff;
uint32_t currentBg2 = random(256);
uint32_t nextBg2 = currentBg2;
int colorripple2;
int center2 = 0;
int step2 = -1;

int diff2;

void ripple()
{
    mapFade = map(userColor, 0, 255, 90, 100);
    fadeRate = mapFade * 0.01;

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
        for (uint16_t l = 0; l < halfofPixels; l++)
        {
            SetRightStripe(l, currentBg);
        }

        if (step == -1)
        {
            center = random(halfofPixels);
            colorripple = random(256);
            step = 0;
        }

        if (step == 0)
        {
            SetRightStripe(center, colorripple);
            step++;
        }
        else
        {
            if (step < maxSteps)
            {
                //  Serial.println(pow(fadeRate, step));

                SetRightStripe(wrap(center + step), colorripple);
                SetRightStripe(wrap(center - step), colorripple);
                if (step > 3)
                {
                    SetRightStripe(wrap(center + step - 3), colorripple);
                    SetRightStripe(wrap(center - step + 3), colorripple);
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
        for (uint16_t l = 0; l < halfofPixels; l++)
        {
            SetLeftStripe(l, currentBg2);
        }

        if (step2 == -1)
        {
            center2 = random(halfofPixels);
            colorripple2 = random(256);
            step2 = 0;
        }

        if (step2 == 0)
        {
            SetLeftStripe(center2, colorripple2);
            step2++;
        }
        else
        {
            if (step2 < maxSteps)
            {
                //  Serial.println(pow(fadeRate, step));

                SetLeftStripe(wrap(center2 + step2), colorripple2);
                SetLeftStripe(wrap(center2 - step2), colorripple2);
                if (step > 3)
                {
                    SetLeftStripe(wrap(center2 + step2 - 3), colorripple2);
                    SetLeftStripe(wrap(center2 - step2 + 3), colorripple2);
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
        return halfofPixels + step;
    if (step > halfofPixels - 1)
        return step - halfofPixels;
    return step;
}
int wrap2(int step)
{
    if (step2 < 0)
        return halfofPixels + step2;
    if (step2 > halfofPixels - 1)
        return step2 - halfofPixels;
    return step2;
}