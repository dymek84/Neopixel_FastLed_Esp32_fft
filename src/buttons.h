#pragma once

#include "Imports.h"

void buttons()
{


    int sensorValue = analogRead(34);

    unsigned long currentMillis = millis();

    if (sensorValue > 86 && sensorValue < 95)
    {


        // button 1
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! next pattern ");
            selected = counter;
        }
        delayss = millis();
    }
    if (sensorValue > 126 && sensorValue < 134)
    {
        menuNumber = 0;
        // button 2
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! Mode MINUS");
            if (counter <= 0)
            {
            }
            else
            {
                counter--;
            }
            Serial.println(selected);
            delayss = millis();
        }
    }
    if (sensorValue > 194 && sensorValue < 205)
    {
        menuNumber = 0;
        // button 3
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! Mode PLUS");
            if (counter >= 16)
            {
            }
            else
            {
                counter++;
            }

            Serial.println(selected);
            delayss = millis();
        }
    }
    if (sensorValue > 162 && sensorValue < 173)
    {
        // button 4
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! stripeBrightness MINUS");

            if (changeLedBright <= 25)
            {
                changeLedBright = 0;
            }
            else if (changeLedBright > 25)
            {
                changeLedBright -= 25;
            }
            menuNumber = 1;
            percentage = map(changeLedBright, 0, 255, 0, 8);
            Serial.println(changeLedBright);
            delayss = millis();
        }
    }
    if (sensorValue > 332 && sensorValue < 342)
    {
        // button 5
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! stripeBrightness PLUS");
            if (changeLedBright > 230)
            {
                changeLedBright = 255;
            }
            else if (changeLedBright < 230)
            {
                changeLedBright += 25;
            }
            menuNumber = 1;
            percentage = map(changeLedBright, 0, 255, 0, 8);
            Serial.println(changeLedBright);
            delayss = millis();
        }
        delayss = millis();
    }
    if (sensorValue > 507 && sensorValue < 512)
    {
        // button 6
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! changeColor MINUS");
            if (changeColor <= 25)
            {
                changeColor = 0;
            }
            else if (changeColor > 25)
            {
                changeColor -= 25;
            }
            menuNumber = 2;
            percentage = map(changeColor, 0, 255, 0, 8);
            Serial.println(changeColor);
        }
        delayss = millis();
    }
    if (sensorValue > 678 && sensorValue < 684)
    {
        // button 7
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! changeColor PLUS");
            if (changeColor > 255)
            {
                changeColor = 255;
            }
            else if (changeColor < 255)
            {
                changeColor += 25;
            }
            menuNumber = 2;
            percentage = map(changeColor, 0, 255, 0, 8);
            Serial.println(changeColor);
        }
        delayss = millis();
    }
    if (sensorValue > 842 && sensorValue < 856)
    {
        // button 8
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! SPEEDS MINUS");
            if (chngePatternSpeed <= 25)
            {
                chngePatternSpeed = 0;
            }
            else if (chngePatternSpeed > 25)
            {
                chngePatternSpeed -= 25;
            }
            menuNumber = 3;
            percentage = map(chngePatternSpeed, 0, 255, 0, 8);
            Serial.println(chngePatternSpeed);
        }
        delayss = millis();
    }
    if (sensorValue > 927 && sensorValue < 934)
    {
        // button 9
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! SPEEDS PLUS");
            if (chngePatternSpeed > 255)
            {
                chngePatternSpeed = 255;
            }
            else if (chngePatternSpeed < 255)
            {
                chngePatternSpeed += 25;
            }
            menuNumber = 3;
            percentage = map(chngePatternSpeed, 0, 255, 0, 8);
            Serial.println(chngePatternSpeed);
        }
        delayss = millis();
    }
    if (sensorValue > 998 && sensorValue < 1006)
    {
        // button 10
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! chageClockBright MINUS");
            if (chageClockBright <= 25)
            {
                chageClockBright = 0;
            }
            else if (chageClockBright > 25)
            {
                chageClockBright -= 25;
            }
            menuNumber = 4;
            percentage = map(chageClockBright, 0, 255, 0, 8);
            Serial.println(chageClockBright);
        }
        delayss = millis();
    }
    if (sensorValue > 1018 && sensorValue < 1023)
    {
        // button 11
        if (millis() - delayss > buttonDebounceTime)
        {
            Serial.println("Button pressed! chageClockBright PLUS");
            if (chageClockBright > 230)
            {
                chageClockBright = 255;
            }
            else if (chageClockBright < 230)
            {
                chageClockBright += 25;
            }
            menuNumber = 4;
            percentage = map(chageClockBright, 0, 255, 0, 8);
            Serial.println(chageClockBright);
        }
        delayss = millis();
    }
}
