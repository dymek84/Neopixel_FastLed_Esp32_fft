

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

#define SAMPLES2 32 // Must be a power of 2
double vReal2[SAMPLES2];
double vImag2[SAMPLES2];

void drawOnSerial(int scale)
{
    String temp = "|";
    for (size_t i = 0; i < scale; i++)
    {
        temp += "=";
    }
    temp += "|";
    Serial.println(temp);
}
void analyzeAudioSerial()
{
    EVERY_N_SECONDS(1)
    {
        for (byte band = 0; band < NUM_BANDS; band++)
        {
            Serial.print(band);
            Serial.print(" : ");
            Serial.print(bandValues[band]);
            drawOnSerial(bandValues[band]);
        }
        Serial.println(" ");
        Serial.println(" xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ");
        Serial.println(" ");
    }
}

void syncTime()
{
    Serial.println("Syncing time...");
    configTime(gmtOffset_sec, dayLightOffset_sec, ntpServer);

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println("");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.println("");
    // setTime(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec,
    //         timeinfo.tm_mday, 1 + timeinfo.tm_mon, 1900 + timeinfo.tm_year);
    //  prevMin = minute();
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    day = timeinfo.tm_mday;
    month = timeinfo.tm_mon + 1;
    year = timeinfo.tm_year + 1900;
    hour = timeinfo.tm_hour;
    minute = timeinfo.tm_min;
    second = timeinfo.tm_sec;
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Rtc.SetDateTime(RtcDateTime(year, month, day, hour, minute, second));
}
void setup()
{
    Serial.begin(115200);
    Serial.print("SDA: ");
    Serial.println(SDA);
    Serial.print("SCL: ");
    Serial.println(SCL);
    Serial.println("Setup Start");
    // Wire.begin(19, 23);
    Serial.println("wire begint");
    if (!RTC.begin())
    {
        Serial.println("Couldn't find RTC");
        // while (1)
        //     ;
    }
    else
    {
        Serial.println("RTC found");
    }
    // RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

    randomSeed(analogRead(A0));
    preferences.begin("settings");
    CurrentStripePatternNumber = preferences.getInt("stripePattern");
    CurrentMatrixPatternNumber = preferences.getInt("matrixPattern");
    currentPaletteStripeIndex = preferences.getInt("stripePalette");
    currentPaletteMatrixIndex = preferences.getInt("matrixPalette");
    micSensytivity = preferences.getInt("micSensytivity");
    micSquelch = preferences.getInt("micNoise");
    matrixSpeed = preferences.getInt("matrixSpeed");
    stripeSpeed = preferences.getInt("stripeSpeed");
    matrixBrightness = preferences.getInt("mBrightness");
    stripBrightness = preferences.getInt("sBrightness");
    welcomeMessage = preferences.getString("WMessage");
    paletteTime = preferences.getInt("paletteTime");
    autoPalMat = preferences.getInt("autoPalMatrix");
    autoPalStr = preferences.getInt("autoPalStr");
    clockOnOff = preferences.getBool("clockOnOff");
    clockColor = stringToCRGB(preferences.getString("clockColor"));
    ssid = preferences.getString("ssid");
    pass = preferences.getString("pass");
    preferences.end();
    currentPaletteStripe = paletteList[currentPaletteStripeIndex].Palette;
    currentPaletteMatrix = paletteList[currentPaletteMatrixIndex].Palette;
    targetPaletteMatrix = currentPaletteMatrix;
    targetPaletteStripe = currentPaletteStripe;
    strip.begin();
    strip.clear();
    strip.show();
    boolean connectedToNetwork = false; // We want to know if we have a network before proceeding

    Serial.println("start");
    MatrtixController = &FastLED.addLeds<WS2812B, MATRIX_DATA_PIN, GRB>(matrix, NUM_LEDS_MATRIX).setCorrection(TypicalSMD5050);
    StripeController = &FastLED.addLeds<WS2812B, STRIPE_DATA_PIN, GRB>(stripe, NUM_LEDS_STRIPE).setCorrection(TypicalSMD5050);

    FastLED.setBrightness(100);
    // The WIFI credentials are stored here
    delay(1000);

    if (connectToNetwork(ssid, pass))
    {
        //  SPIFFS
        if (!SPIFFS.begin(true))
        {
            Serial.println("An Error has occurred while mounting SPIFFS");
            return;
        }
        else
        {
            listDir(SPIFFS, "/", 2);
        }
        initWebServer();
        // runString(WiFi.localIP().toString(), CRGB::White, 15);
        // FastLED.delay(1000); // to allow to start the 2nd processor.
        Serial.println("connectedToNetwork");
        connectedToNetwork = true;
        Serial.println("true");
    }
    else
    {
        Serial.println("No WIFI, let's offer an accesspoint");
        //  SPIFFS
        if (!SPIFFS.begin(true))
        {
            Serial.println("An Error has occurred while mounting SPIFFS");
            return;
        }
        else
        {
            listDir(SPIFFS, "/", 2);
        }
        RunAPmode();
        runString(WiFi.softAPIP().toString(), CRGB::White, 15);
        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = false;
    }
    Serial.println("1");
    // runString(WiFi.localIP().toString(), CRGB::White, 1);

    Serial.println("preferences.end");

    sampling_period_us = (1.0 / SAMPLING_FREQ) * pow(10.0, 6);

    syncTime();
    setup_i2s();
    // runString(welcomeMessage, CRGB::Red, 20);
    Serial.println("setup done");
}

void loop()
{
    // now = Rtc.GetDateTime();
    now = RTC.now();
    read_i2c_fft();
    //i2s_read_fft2();
    mappedMatrixInterval = map(matrixSpeed, 0, 255, 255, 0) + patternMatrixInterval;
    mappedStripeInterval = map(stripeSpeed, 0, 255, 255, 0) + patternStripeInterval;
    // Serial.println("1");
    EVERY_N_MILLISECONDS(40)
    {
        nblendPaletteTowardPalette(currentPaletteStripe, targetPaletteStripe, 12);
        nblendPaletteTowardPalette(currentPaletteMatrix, targetPaletteMatrix, 12);
    }
    // Serial.println("2");
    if (autoPalMat)
    {
        EVERY_N_SECONDS(paletteTime)
        {
            nextPaletteMatrix(true);
        }
    }
    if (autoPalStr)
    {
        EVERY_N_SECONDS(paletteTime)
        {
            nextPaletteStripe(true);
        }
    }
    // Serial.println("3");

    if (millis() - lastUpdateStripe > mappedStripeInterval)
    {
        colorHueStripe++;
        patternStripeInterval = 0;
        patternsStripe[CurrentStripePatternNumber].drawFrame();
        lastUpdateStripe = millis();
    }
    if (showMessage)
    {
    }
    else
    {
        if (millis() - lastUpdateMatrix > mappedMatrixInterval)
        {
            colorHueMatrix++;
            patternMatrixInterval = 0;
            patternsMatrix[CurrentMatrixPatternNumber].drawFrame();
            lastUpdateMatrix = millis();
        }
        if (patternsMatrix[CurrentMatrixPatternNumber].name == "StrobeAndDiffusion" || messageIsShown || patternsMatrix[CurrentMatrixPatternNumber].name == "Falling Colors")
        {
        }
        else
        {
            if (clockOnOff)
                drawTime(1, 0, clockColor, true, true);
        }
    }
    MatrtixController->showLeds(matrixBrightness);
    StripeController->showLeds(stripBrightness);
}
void nextPaletteStripe(bool isAuto)
{
    preferences.begin("settings", false);
    if (isAuto)
    {
        currentPaletteStripeIndex >= NUMpalettes ? currentPaletteStripeIndex = 0 : currentPaletteStripeIndex++;
    }
    else
    {
        currentPaletteStripeIndex = (currentPaletteStripeIndex + 1) % NUMpalettes;
    }
    targetPaletteStripe = paletteList[currentPaletteStripeIndex].Palette;
    preferences.putInt("stripePalette", currentPaletteStripeIndex);
    preferences.end();
}
void prevPaletteStripe()
{
    preferences.begin("settings", false);
    currentPaletteStripeIndex <= 0 ? currentPaletteStripeIndex = 0 : currentPaletteStripeIndex--;
    targetPaletteStripe = paletteList[currentPaletteStripeIndex].Palette;
    preferences.putInt("stripePalette", currentPaletteStripeIndex);
    preferences.end();
}
void nextPaletteMatrix(bool isAuto)
{
    preferences.begin("settings", false);
    if (isAuto)
    {
        currentPaletteMatrixIndex >= NUMpalettes ? currentPaletteMatrixIndex = 0 : currentPaletteMatrixIndex++;
    }
    else
    {
        currentPaletteMatrixIndex = (currentPaletteMatrixIndex + 1) % NUMpalettes;
    }
    targetPaletteMatrix = paletteList[currentPaletteMatrixIndex].Palette;
    preferences.putInt("matrixPalette", currentPaletteMatrixIndex);
    preferences.end();
}
void prevPaletteMatrix()
{
    preferences.begin("settings", false);
    currentPaletteMatrixIndex <= 0 ? currentPaletteMatrixIndex = 0 : currentPaletteMatrixIndex--;
    targetPaletteMatrix = paletteList[currentPaletteMatrixIndex].Palette;
    preferences.putInt("matrixPalette", currentPaletteMatrixIndex);
    preferences.end();
}
void nextPatternStripe()
{
    preferences.begin("settings", false);
    CurrentStripePatternNumber >= StripePatternsAmount ? CurrentStripePatternNumber = StripePatternsAmount : CurrentStripePatternNumber++;
    isAudioStripe = patternsStripe[CurrentStripePatternNumber].isAudio;

    FastLED.clear();
    preferences.putInt("stripePattern", CurrentStripePatternNumber);
    // runString(patternsStripe[CurrentStripePatternNumber].name, CRGB::White, 1);
    preferences.end();
}
void prevPatternStripe()
{
    preferences.begin("settings", false);
    CurrentStripePatternNumber <= 0 ? CurrentStripePatternNumber = 0 : CurrentStripePatternNumber--;
    isAudioStripe = patternsStripe[CurrentStripePatternNumber].isAudio;

    FastLED.clear();
    preferences.putInt("stripePattern", CurrentStripePatternNumber);
    preferences.end();
}
void nextPatternMatrix()
{
    preferences.begin("settings", false);
    CurrentMatrixPatternNumber >= MatrixPatternsAmount ? CurrentMatrixPatternNumber = MatrixPatternsAmount : CurrentMatrixPatternNumber++;
    isAudioMatrix = patternsMatrix[CurrentMatrixPatternNumber].isAudio;
    FastLED.clear();
    preferences.putInt("matrixPattern", CurrentMatrixPatternNumber);
    preferences.end();
}
void prevPatternMatrix()
{
    preferences.begin("settings", false);
    CurrentMatrixPatternNumber <= 0 ? CurrentMatrixPatternNumber = 0 : CurrentMatrixPatternNumber--;
    isAudioMatrix = patternsMatrix[CurrentMatrixPatternNumber].isAudio;
    FastLED.clear();
    preferences.putInt("matrixPattern", CurrentMatrixPatternNumber);
    preferences.end();
}
void setBrightMatrix(uint8_t bright)
{
    preferences.begin("settings", false);
    matrixBrightness = bright;
    Serial.println(String(matrixBrightness));
    preferences.putInt("mBrightness", matrixBrightness);
    preferences.end();
}
void setBrightStripe(uint8_t bright)
{
    preferences.begin("settings", false);
    stripBrightness = bright;
    Serial.println(String(stripBrightness));
    preferences.putInt("sBrightness", stripBrightness);
    preferences.end();
}
void setSpeedMatrix(uint16_t speed)
{
    preferences.begin("settings", false);
    matrixSpeed = speed;
    Serial.println(String(matrixSpeed));
    preferences.putInt("matrixSpeed", matrixSpeed);
    preferences.end();
}
void setSpeedStripe(uint16_t speed)
{
    preferences.begin("settings", false);
    stripeSpeed = speed;
    Serial.println(String(stripeSpeed));
    preferences.putInt("stripeSpeed", stripeSpeed);
    preferences.end();
}

void minimumDelayFromPatternsMatrix(uint16_t delay)
{
    patternMatrixInterval = delay;
}
void minimumDelayFromPatternsStripe(uint16_t delay)
{
    patternStripeInterval = delay;
}