
long delayss = 0;
long delayEEPROM = 0;
void buttons()
{
    // int buttonVal = digitalRead(button);

    int sensorValue = analogRead(A1);

    unsigned long currentMillis = millis();
    if (sensorValue > 86 && sensorValue < 1023)
    {
        if (showMenu)
        {
            moreTime = true;
        }
        else
        {
            showMenu = true;
        }
        if (millis() - delayEEPROM > (1000 * 60))
        {
            EEPROM.update(0, selected);
            EEPROM.update(1, stripeBrightness);
            EEPROM.update(2, COLORS);
            EEPROM.update(3, patternInterval);
            EEPROM.update(4, clockBright);
            delayEEPROM = millis();
            Serial.println("EEPROM Updated");
        }
    }
    if (sensorValue > 86 && sensorValue < 95)
    {
        // button 1
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! SELECT ");
            selected = counter;
            AllOff();
        }
        delayss = millis();
    }
    if (sensorValue > 126 && sensorValue < 134)
    {
        menuname = 0;
        // button 2
        if (millis() - delayss > 200)
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
        menuname = 0;
        // button 3
        if (millis() - delayss > 200)
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
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! stripeBrightness MINUS");

            if (stripeBrightness <= 25)
            {
                stripeBrightness = 0;
            }
            else if (stripeBrightness > 25)
            {
                stripeBrightness -= 25;
            }
            menuname = 1;
            percentage = map(stripeBrightness, 0, 255, 0, 8);
            Serial.println(stripeBrightness);
            delayss = millis();
        }
    }
    if (sensorValue > 332 && sensorValue < 342)
    {
        // button 5
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! stripeBrightness PLUS");
            if (stripeBrightness > 230)
            {
                stripeBrightness = 255;
            }
            else if (stripeBrightness < 230)
            {
                stripeBrightness += 25;
            }
            menuname = 1;
            percentage = map(stripeBrightness, 0, 255, 0, 8);
            Serial.println(stripeBrightness);
            delayss = millis();
        }
        delayss = millis();
    }
    if (sensorValue > 507 && sensorValue < 512)
    {
        // button 6
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! COLORS MINUS");
            if (COLORS <= 25)
            {
                COLORS = 0;
            }
            else if (COLORS > 25)
            {
                COLORS -= 25;
            }
            menuname = 2;
            percentage = map(COLORS, 0, 255, 0, 8);
            Serial.println(COLORS);
        }
        delayss = millis();
    }
    if (sensorValue > 678 && sensorValue < 684)
    {
        // button 7
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! COLORS PLUS");
            if (COLORS > 255)
            {
                COLORS = 255;
            }
            else if (COLORS < 255)
            {
                COLORS += 25;
            }
            menuname = 2;
            percentage = map(COLORS, 0, 255, 0, 8);
            Serial.println(COLORS);
        }
        delayss = millis();
    }
    if (sensorValue > 842 && sensorValue < 856)
    {
        // button 8
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! SPEEDS MINUS");
            if (patternInterval <= 25)
            {
                patternInterval = 0;
            }
            else if (patternInterval > 25)
            {
                patternInterval -= 25;
            }
            menuname = 3;
            percentage = map(patternInterval, 0, 255, 0, 8);
            Serial.println(patternInterval);
        }
        delayss = millis();
    }
    if (sensorValue > 927 && sensorValue < 934)
    {
        // button 9
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! SPEEDS PLUS");
            if (patternInterval > 255)
            {
                patternInterval = 255;
            }
            else if (patternInterval < 255)
            {
                patternInterval += 25;
            }
            menuname = 3;
            percentage = map(patternInterval, 0, 255, 0, 8);
            Serial.println(patternInterval);
        }
        delayss = millis();
    }
    if (sensorValue > 998 && sensorValue < 1006)
    {
        // button 10
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! clockBright MINUS");
            if (clockBright <= 25)
            {
                clockBright = 0;
            }
            else if (clockBright > 25)
            {
                clockBright -= 25;
            }
            menuname = 4;
            percentage = map(clockBright, 0, 255, 0, 8);
            Serial.println(clockBright);
        }
        delayss = millis();
    }
    if (sensorValue > 1018 && sensorValue < 1023)
    {
        // button 11
        if (millis() - delayss > 200)
        {
            Serial.println("Button pressed! clockBright PLUS");
            if (clockBright > 230)
            {
                clockBright = 255;
            }
            else if (clockBright < 230)
            {
                clockBright += 25;
            }
            menuname = 4;
            percentage = map(clockBright, 0, 255, 0, 8);
            Serial.println(clockBright);
        }
        delayss = millis();
    }
}