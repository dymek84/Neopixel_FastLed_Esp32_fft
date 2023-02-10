
#ifndef _MAIN_INO__AA_
#define _MAIN_INO__AA_

#include "Imports.h"
/*                                            	    																		                   ▄███▄
  --------------------------------------------------------------------------------------------------------------------------------------------█----█-----------
|  O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O█O O █ O O O O  |
|  O         O   O O   O         O   O O O   O O   O O O   O           O   O O   O O         O   O O O   O   O         O   O O O O O O O O O O█O O █ O O O O  |
|  O   O O O O   O O   O   O O O O   O O   O O O O   O   O O   O O O   O   O O   O O   O O O O     O     O   O   O O O O   O O O O O O O O O O█O O █ O O O O  |
|  O   O O O O   O O   O   O O O O   O   O O O O O O   O O O   O O O   O   O O   O O   O O O O   O   O   O   O   O O O O   O O O O O O▄███▄████O O ███▄O O O  |
|  O         O   O O   O   O O O O     O O O O O O O   O O O   O O O   O   O O   O O         O   O O O   O   O         O   O O O O O O█O O█O O█O O █ O ███ O  |
|  O   O O O O   O O   O   O O O O   O   O O O O O O   O O O   O O O   O   O O   O O   O O O O   O O O   O   O   O O O O   O O O O O O█O O█O O█O O █ O █  █O  |
|  O   O O O O   O O   O   O O O O   O O   O O O O O   O O O   O O O   O   O O   O O   O O O O   O O O   O   O   O O O O   O O O O O O█O O O O█O O █ O O █ O  |
|  O   O O O O         O         O   O O O   O O O O   O O O           O         O O         O   O O O   O   O         O         O O O█ O O O O O O O O█ O O  |
|  O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O  |
--------------------------------------------------------------------------------------------------------------------------------------------------------------

 */
void setup()
{
    Serial.begin(115200);

    unsigned long setupStartTime = millis();
    while (!Serial && millis() - setupStartTime < 3000)
        ;

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(matrix, NUM_LEDS_MATRIX).setCorrection(TypicalLEDStrip); // Initialize NEO_MATRIX
    FastLED.addLeds<LED_TYPE, strip1_PIN, COLOR_ORDER>(strip1, LED_STRIP_PIXELS_AMOUNT).setCorrection(TypicalLEDStrip);

    FastLED.setBrightness(255);
    Serial.println("start");
    Wire.begin();
    // rtc.begin(21, 22);
    //  07:22:55.606 -> I2C device found at address 0x3C
    //  07:22:55.653 -> I2C device found at address 0x50
    //  07:22:55.653 -> I2C device found at address 0x68

    // rtc.DSadjust(07, 01, 21, 2022, 12, 27); // 00:19:21 16 Mar 2022}
    randomSeed(analogRead(1));
    selected = EEPROM.read(0);
    counter = selected;
    changeLedBright = EEPROM.read(1);
    changeColor = EEPROM.read(2);
    chngePatternSpeed = EEPROM.read(3);
    chageClockBright = EEPROM.read(4);
    pinMode(audio, INPUT);

    matrix2.begin();
    matrix2.setTextWrap(false);
    matrix2.setBrightness(100);
    matrix2.setTextColor(electric_pumpkinaaaaaa);
    // scrollText();

    Serial.println("setup done");
}
/*void intro()
{
  EVERY_N_MILLISECONDS(50)
  {
    gHue >= 255 ? gHue = 0 : gHue++;
    fill_rainbow(strip1, 15, gHue - 1, 7);
    fill_rainbow(strip2, 15, gHue - 2, 7);
    fill_rainbow(strip3, 15, gHue - 3, 7);
    fill_rainbow(strip4, 15, gHue - 4, 7);
    fill_rainbow(strip5, 15, gHue - 5, 7);
    fill_rainbow(strip6, 15, gHue - 6, 7);
    fill_rainbow(strip7, 15, gHue - 7, 7);
    fill_rainbow(strip8, 15, gHue - 8, 7);
    fill_rainbow(strip9, 15, gHue - 9, 7);
    fill_rainbow(strip10, 15, gHue - 10, 7);
    fill_rainbow(strip11, 15, gHue - 11, 7);
    fill_rainbow(strip12, 15, gHue - 12, 7);
    FastLED.show();
  }
}*/

void loop()
{
    Visualizer();
    // Visualizer();
    //  test2(CRGB::Red);
    //  test(CRGB::Blue);

    // displayVUWhite();
    // EVERY_N_MILLISECONDS(500) { gHue >= 255 ? gHue = 0 : gHue++; }
    if (millis() - startTime >= 100)
    {

        startTime = millis();
    }

    //   buttons();

    //  displayUpdate(map(chageClockBright, 0, 20, 0, 255));
    //  buttons();
    // inputState = digitalRead(modeButtonSelect);
    /* if (showMenu == false)
     {
       // clock(tm.Hour, tm.Minute, false, 0, 0);
       moreTime = false;
       startTime = millis();
     }
     else if (showMenu == true)
     {
       //  clock(counter, selected, true, menuname, percentage);
       if (millis() - startTime >= timeOut)
       {
         showMenu = false;
         moreTime = false;
       }
       if (moreTime)
       {
         startTime = millis();
         moreTime = false;
       }
     }*/
    //  unsigned long currentMillis = millis();

    // setBrightness(stripeBrightness);
    EVERY_N_SECONDS(20)
    {
        nextPattern();

        Serial.print(currentPatternName);
        Serial.print(" - number: ");
        Serial.print(gCurrentPatternNumber);
        Serial.print(" - TOTAL: ");
        Serial.println("16");

    } // change patterns periodically
    updatePattern(gCurrentPatternNumber);
}

void nextPattern()
{
    gCurrentPatternNumber == 7 ? gCurrentPatternNumber = 0 : gCurrentPatternNumber++;
    FastLED.clear();
}

void test()
{
    currentPatternName = "test";
    if (millis() - startTime >= 5)
    {
        startTime = millis();

        for (int x = 0; x < LED_STRIP_PIXELS_AMOUNT; x++)
        {

            setPixelRGB(x, CRGB::Yellow);
            FastLED.show();
            setPixelRGB(x, CRGB::Black);
        }
    }
}
CRGB coliber;
long randomTime = 0;
void test2()
{

    if (millis() - randomTime >= 2)
    {
        randomTime = millis();
        coliber = arrayofcolors[random(18)];
    }
    currentPatternName = "test2";
    if (millis() - startTime >= 2)
    {
        startTime = millis();

        // This outer loop will go over each strip, one at a time
        for (int x = 0; x < LED_STRIP_PIXELS_AMOUNT; x++)
        {

            setPixelRGB(x, coliber);
            FastLED.show();
        }
    }
}
void buttons()
{
    // int buttonVal = digitalRead(button);
    /*
      int sensorValue = analogRead(34);

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

        EEPROM.write(0, selected);
        EEPROM.write(1, changeLedBright);
        EEPROM.write(2, changeColor);
        EEPROM.write(3, chngePatternSpeed);
        EEPROM.write(4, chageClockBright);
        // delayEEPROM = millis();
        Serial.println("EEPROM Updated");
      }
      for (int i = 0; i < 12; i++)
      {
        if (sensorValue > buttonsValues[i][0] && sensorValue < buttonsValues[i][1])
        {
          // button 1
          if (millis() - delayss > 200)
          {
            // Serial.println("Button pressed! SELECT ");
            //  selected = counter;
            // AllOff();
            delayss = millis();
          }
        }
      }*/
}
void updatePattern(int pat)
{ // call the pattern currently being created
    switch (pat)
    {
    case 0:
        displayVURainbow();
        break;
    case 1:
        displayVURainbow();
        break;
    case 2:
        displayVU();
        break;
    case 3:
        bpm();
        break;
    case 4:
        displayVUWhite();
        break;
    case 5:
        rainbow();
        break;
    case 6:
        test();
        break;
    case 7:
        test2();
        break;
    case 8:

        break;
    case 9:

        break;
    case 10:

        break;
    case 11:

        break;
    }
}
void Visualizer()
{
    // Collect Samples
    getSamples();
    // Update Display
    // displayVU();
}
void getSamples()
{
    for (int i = 0; i < SAMPLES; i++)
    {
        vReal[i] = analogRead(audio) * MULTIPLY_BY;
        vImag[i] = 0;
    }

    // FFT
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    // Update Intensity Array
    for (int i = 2; i < (6 * Displacement) + 2; i += 2)
    {
        vReal[i] = constrain(vReal[i], 0, 2047);    // set max value for input data
        vReal[i] = map(vReal[i], 0, 2047, 0, yres); // map data to fit our display

        Intensity[(i / Displacement) - 2]--;              // Decrease displayed value
        if (vReal[i] > Intensity[(i / Displacement) - 2]) // Match displayed value to measured value
            Intensity[(i / Displacement) - 2] = vReal[i];
    }
}
void scrollText()
{
    CRGB color = arrayofcolors[random8(8)];
    for (int i = 0; i < 80; i++)
    {

        matrix2.fillScreen(0); // Turn off all the LEDs
        matrix2.setCursor(x2, 0);
        matrix2.print(F("Welcome Emiel"));
        if (--x2 < -80)
        {
            x2 = matrix2.width();
            if (++pass >= 8)
                pass = 0;
            matrix2.setTextColor(color);
        }
        matrix2.show();
        delay(20);
    }
    delay(1000);
}

void displayVU()
{
    currentPatternName = "displayVU";

    FastLED.clear();

    for (int i = 0; i < Intensity[0]; i++)
    {
        strip1[i + LED_STRIP_PIXELS_AMOUNT / 2] = arrayofcolors[0];
        strip1[LED_STRIP_PIXELS_AMOUNT / 2 - i] = arrayofcolors[0];
    }

    FastLED.show();
}

void displayVUWhite()
{
    currentPatternName = "VuWhite";
    FastLED.clear();

    for (int i = 0; i < Intensity[0]; i++)
    {
        strip1[i + LED_STRIP_PIXELS_AMOUNT / 2] = CRGB::White;
        strip1[LED_STRIP_PIXELS_AMOUNT / 2 - i] = CRGB::White;
    }

    FastLED.show();
}
int countplus = 0;
void displayVURainbow()
{
    currentPatternName = "VURainbow";
    FastLED.clear();
    for (int i = 0; i < Intensity[0]; i++)
    {
        strip1[i + LED_STRIP_PIXELS_AMOUNT / 2] = CHSV(((i * 256 / 12) + 10 + countplus), 255, bright);
        strip1[LED_STRIP_PIXELS_AMOUNT / 2 - i] = CHSV(((i * 256 / 12) + 10 + countplus), 255, bright);
    }

    countplus == 255 ? countplus = 0 : countplus += 5;
    FastLED.show();
}
void displayUpdate(int bright)
{
    int color = 0;
    for (int i = 0; i < xres; i++)
    {
        for (int j = 0; j < yres; j++)
        {
            if (j <= Intensity[i])
            { // Light everything within the intensity range
                if (j % 2 == 0)
                {
                    matrix[((xres * (j + 1)) - i - 1)] = CHSV(color, 255, bright);
                    matrix[255 - ((xres * (j + 1)) - i - 1)] = CHSV(color, 255, bright);
                }
                else
                {
                    matrix[((xres * j) + i)] = CHSV(color, 255, bright);
                    matrix[255 - ((xres * j) + i)] = CHSV(color, 255, bright);
                }
            }
            else
            { // Everything outside the range goes dark
                if (j % 2 == 0)
                {
                    matrix[((xres * (j + 1)) - i - 1)] = CHSV(color, 255, 0);
                    matrix[255 - ((xres * (j + 1)) - i - 1)] = CHSV(color, 255, 0);
                }
                else
                {
                    matrix[((xres * j) + i)] = CHSV(color, 255, 0);
                    matrix[255 - ((xres * j) + i)] = CHSV(color, 255, 0);
                }
            }
        }
        color += 255 / xres; // Increment the Hue to get the Rainbow
    }
    FastLED.show();
}

void rainbow() // rainbowWithGlitter()//confetti
{
    currentPatternName = "Rainbow";

    static uint16_t j = 0;
    for (int i = 0; i < LED_STRIP_PIXELS_AMOUNT; i++)
    {
        setPixelRGB(i, Wheel(((i * 256 / LED_STRIP_PIXELS_AMOUNT) + j)));
    }
    FastLED.show();
    j++;
    if (j >= 256)
        j = 0;
}

void bpm()
{
    currentPatternName = "bpm";
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++)
    { // 9948
        setPixelRGB(i, ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10)));
    }
    FastLED.show();
}

void setPixelHSV(int i, CHSV colorHSV)
{
    CRGB dupa = CRGB(0, 0, 0);
    setPixel(i, colorHSV, dupa, true);
}
void setPixelRGB(int i, CRGB colorRGB)
{
    CHSV dupa = CHSV(0, 0, 0);
    setPixel(i, dupa, colorRGB, false);
}
void mirrorSides(int pixel, CHSV colorCHSV, CRGB colorRGB, boolean isHSV)
{
    if (pixel > halfofPixels)
    {
        Serial.println("Pixel number too high, over half for mirror image");
    }
    else
    {

        isHSV ? (strip1[pixel] = colorCHSV) : (strip1[pixel] = colorRGB);
        isHSV ? (strip1[pixel] = colorCHSV) : (strip1[pixel] = colorRGB);
    }
}
void setPixel(int pixel, CHSV colorCHSV, CRGB colorRGB, boolean isHSV)
{

    isHSV ? (strip1[pixel] = colorCHSV) : (strip1[pixel] = colorRGB);
}
void setLeftSide(int pixel, CHSV colorCHSV, CRGB colorRGB, boolean isHSV)
{
    isHSV ? (strip1[halfofPixels - pixel] = colorCHSV) : (strip1[halfofPixels - pixel] = colorRGB);
}
void setRightSide(int pixel, CHSV colorCHSV, CRGB colorRGB, boolean isHSV)
{
    isHSV ? (strip1[pixel] = colorCHSV) : (strip1[pixel] = colorRGB);
}
void setCorner(int cornerNumber, int pixel, CHSV colorCHSV, CRGB colorRGB, boolean isHSV)
{

    int additionalNumber;
    switch (cornerNumber)
    {
    case 1:
        additionalNumber = firstCornerPixelNumber;
        break;
    case 2:
        additionalNumber = secondCornerPixelNumber;
        break;
    case 3:
        additionalNumber = thirdCornerPixelNumber;
        break;
    case 4:
        additionalNumber = fourthCornerPixelNumber;
        break;
        isHSV ? (strip1[pixel + additionalNumber] = colorCHSV) : (strip1[pixel + additionalNumber] = colorRGB);
    }
}
CRGB Wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}
#endif
