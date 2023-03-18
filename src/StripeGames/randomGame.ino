
#pragma once

#include "Imports.h"
/*
static bool blink = false;
int aaaaaa = 0;
int asdf = 0;
int fase = 1;
int myRandom;
long timepass = 0;
CRGB randmsColors[12];
bool shuffle = true;
int slowDown = 20;
bool button1Pressed, button2Pressed;
void randomGame()
{
    for (uint8_t i = 0; i < 12; i++)
    {
        randmsColors[i] = i * 21.33;
    }

    if (button1Pressed)
    {
        fase = 1;
        shuffle = true;
        button1Pressed = false;
        //FastLED.clear();
    }
    if (button2Pressed)
    {
        fase = 2;
        button2Pressed = false;
    }
    switch (fase)
    {
    case 1:
        asdf = 0;
        selectStripeFase();
        break;
    case 2:
        randomFase();
        break;
    case 3:
        buttonPressed();
        break;
    case 4:
        winnerFase();
        break;
    }
}

void selectStripeFase()
{

    if (shuffle)
    {
        shuffleColors();
        shuffle = false;
    }
    FastLED.show();
    // AllOff();
    for (int i = 0; i < NUM_LEDS_STRIPE / 2; i++)
    {
        stripe[i + NUM_LEDS_STRIPE] =  randmsColors[1]);
    }
}
void randomFase()
{
    aaaaaa++;
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - timepass > 10)
    {

        myRandom = random(12) + 1;
        setStripe(myRandom);
        timepass = millis();
    }
    if (aaaaaa >= 200)
    {
        aaaaaa = 0;
        fase = 3;
    }
}
void buttonPressed()
{
    Serial.print(" patternInterval: ");
    Serial.println(patternInterval);

    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - timepass > slowDown)
    {
        if (slowDown < patternInterval * 2)
        {
            slowDown += 20;
        }
        else if (slowDown < patternInterval * 6)
        {
            slowDown += 100;
        }
        else
        {
            slowDown = 20;
            fase = 4;
        }
        myRandom = random(12);
        setStripe(myRandom);
        timepass = millis();
    }
}

void winnerFase()
{
    if (asdf < 20)
    {
        unsigned long currentMillis = millis(); // Start of sample window
        if (currentMillis - timepass > 300)
        {
            asdf++;
            if (blink)
            {
                setStripe(myRandom);
            }
            else
            {
                AllOff();
                FastLED.show();
            }
            blink = !blink;
            timepass = millis();
        }
    }
    else
    {
        setStripe(myRandom);
    }
}

void setStripe(int stripeNumber)
{
    // AllOff();
    if (stripeNumber == 1)
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            pixels.setPixelColor(i, colors[randmsColors[0]]);
        }
    }
    else
    {
        pixels.clear();
        pixels.show();
    }
    if (stripeNumber == 2)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip1.setPixelColor(i, colors[randmsColors[1]]);
        }
    }
    else
    {
        strip1.clear();
        strip1.show();
    }
    if (stripeNumber == 3)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip2.setPixelColor(i, colors[randmsColors[2]]);
        }
    }
    else
    {
        strip2.clear();
        strip2.show();
    }
    if (stripeNumber == 4)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip3.setPixelColor(i, colors[randmsColors[3]]);
        }
    }
    else
    {
        strip3.clear();
        strip3.show();
    }
    if (stripeNumber == 5)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip4.setPixelColor(i, colors[randmsColors[4]]);
        }
    }
    else
    {
        strip4.clear();
        strip4.show();
    }
    if (stripeNumber == 6)
    {
        for (int i = 0; i < longerstrip; i++)
        {
            strip5.setPixelColor(i, colors[randmsColors[5]]);
        }
    }
    else
    {
        strip5.clear();
        strip5.show();
    }
    if (stripeNumber == 7)
    {
        for (int i = 0; i < longerstrip; i++)
        {
            strip6.setPixelColor(i, colors[randmsColors[6]]);
        }
    }
    else
    {
        strip6.clear();
        strip6.show();
    }
    if (stripeNumber == 8)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip7.setPixelColor(i, colors[randmsColors[7]]);
        }
    }
    else
    {
        strip7.clear();
        strip7.show();
    }
    if (stripeNumber == 9)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip8.setPixelColor(i, colors[randmsColors[8]]);
        }
    }
    else
    {
        strip8.clear();
        strip8.show();
    }
    if (stripeNumber == 10)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip9.setPixelColor(i, colors[randmsColors[9]]);
        }
    }
    else
    {
        strip9.clear();
        strip9.show();
    }
    if (stripeNumber == 11)
    {
        for (int i = 0; i < shortstrip; i++)
        {
            strip10.setPixelColor(i, colors[randmsColors[10]]);
        }
    }
    else
    {
        strip10.clear();
        strip10.show();
    }
    if (stripeNumber == 12)
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            strip11.setPixelColor(i, colors[randmsColors[11]]);
        }
    }
    else
    {
        strip11.clear();
        strip11.show();
    }
    FastLED.show();
}
void shuffleColors()
{
    int newRand[12] = {
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
        random(6),
    };
    for (int i = 0; i < 12; i++)
    {
        randmsColors[i] = newRand[i];
    }
}

*/