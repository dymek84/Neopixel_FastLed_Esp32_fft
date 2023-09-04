
#pragma once

#include "Imports.h"

#define BAND_GAME_NUMBERS 8
static bool blink = false;
int aaaaaa = 0;
int asdf = 0;
int fase = 1;
int myRandom;
long timepass = 0;
CHSV randmsColors[8];
bool shuffle = true;
int slowDown = 20;
bool button1Pressed, button2Pressed, needSetup = true;

void setStripe(int stripeNumber)
{
    int startStripe;
    int endStripe;

    if (stripeNumber == 0)
    {
        startStripe = 2;
        endStripe = NUM_LEDS_STRIPE / BAND_GAME_NUMBERS - 2;
    }
    else
    {
        startStripe = NUM_LEDS_STRIPE / BAND_GAME_NUMBERS * (stripeNumber - 1) + 2;
        endStripe = NUM_LEDS_STRIPE / BAND_GAME_NUMBERS * stripeNumber - 2;
    }

    for (int j = startStripe; j < endStripe; j++)
    {
        stripe[j] = randmsColors[stripeNumber];
    }
}

void selectStripeFase()
{
    for (uint8_t i = 0; i < BAND_GAME_NUMBERS; i++)
    {
        setStripe(i);
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
                fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 200);
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
void setupGame()
{
    for (uint8_t i = 0; i < BAND_GAME_NUMBERS; i++)
    {
        randmsColors[i] = CHSV(i * (256 / BAND_GAME_NUMBERS), 255, 255);
    }
    needSetup = false;
    Serial.println("Setup Game");
}
void randomGame()
{

    if (needSetup)
    {
        setupGame();
        needSetup = false;
    }
    if (button1Pressed)
    {
        fase = 1;
        shuffle = true;
        button1Pressed = false;
        // FastLED.clear();
    }
    if (button2Pressed)
    {
        fase = 2;
        button2Pressed = false;
    }
    EVERY_N_SECONDS(1)
    {
        Serial.print("Fase: ");
        Serial.println(fase);
    }
    switch (fase)
    {
    case 1:
        asdf = 0;
        selectStripeFase();
        break;
    case 2:
        //  randomFase();
        break;
    case 3:
        //  buttonPressed();
        break;
    case 4:
        //  winnerFase();
        break;
    default:
        setStripe(myRandom);
        break;
    }
}