

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

// const uint8_t paletteCount = ARRAY_SIZE(paletteList);
void nextPalette()
{

    currentPaletteIndex = (currentPaletteIndex + 1) % NUMpalettes;
    targetPalette = paletteList[currentPaletteIndex].Palette;
}
boolean connectToNetwork(String s, String p)
{
    const char *ssid = s.c_str();
    const char *password = p.c_str();

    Serial.print("ACCESSING WIFI: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(2000);
        Serial.println("Connecting to WiFi..");
        if (timeout == 5)
        {
            return false;
            break;
        }
        Serial.println(".");
        timeout++;
    }
    Serial.println(WiFi.localIP());
    return true;
} // network()
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

    Rtc.SetDateTime(RtcDateTime(year, month, day, hour, minute, second));
}
void setup()
{

    Rtc.Begin();
    RtcDateTime now = Rtc.GetDateTime();

    strip.begin();
    strip.clear();
    strip.show();
    boolean connectedToNetwork = false; // We want to know if we have a network before proceeding
    Serial.begin(115200);
    Serial.println("start");
    FastLED.addLeds<CHIPSET, LED_PIN_MATRIX, COLOR_ORDER>(matrix, NUM_LEDS_MATRIX).setCorrection(TypicalLEDStrip); // Initialize NEO_MATRIX
    FastLED.addLeds<CHIPSET, LED_PIN_STRIPE, COLOR_ORDER>(stripe, NUM_LEDS_STRIPE).setCorrection(TypicalLEDStrip);

    FastLED.setBrightness(100);
    preferences.begin("wificreds", false); // The WIFI credentials are stored here
    delay(1000);

    preferences.getString("ssid");
    if (connectToNetwork(preferences.getString("ssid"), preferences.getString("password")))
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
        // RunWebserver();

        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = true;
    }
    else
    {
        Serial.println("No WIFI, let's offer an accesspoint");

        RunAPmode();

        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = false;
    }
    while (!connectedToNetwork)
    { // When we are not connected to a router (wifi point) we should not proceed. But only show the accesspoint website
        EVERY_N_SECONDS(30)
        {
            // Serial.println("ESP Matrix Clock is in AccessPoint mode. Please enter your SSID and Key in the Accesspoint website (connect to the AP-wifi first)");
            //   displayIPAP();
        }
    }
    runString(WiFi.localIP().toString(), CRGB::White, 1);
    /// runString(WiFi.localIP().toString(), CRGB::White, 1);
    pinMode(MIC_IN_PIN, INPUT);
    preferences.end();
    Serial.println("preferences.end");
    setupWebServer();
    sampling_period_us = (1.0 / SAMPLING_FREQ) * pow(10.0, 6);

    syncTime();
    preferences.begin("patterns", false);
    CurrentStripePatternNumber = preferences.getInt("stripePattern");
    Serial.println("stripePattern = " + String(CurrentStripePatternNumber));
    CurrentMatrixPatternNumber = preferences.getInt("matrixPattern");
    Serial.println("matrixPattern = " + String(CurrentMatrixPatternNumber));
    overAllBrightness = preferences.getInt("oaBrightness");
    Serial.println("oaBrightness = " + String(overAllBrightness));
    preferences.end();
    preferences.begin("matrixsettings", false);
    welcommessage = preferences.getString("welcommessage");
    runString(welcommessage, CRGB::Red, 20);
    preferences.end();

    Serial.println("setup done");
}

void loop()
{
    now = Rtc.GetDateTime();

    processAudio();
    EVERY_N_MILLISECONDS(500)
    {
        colorTimer++;
    }
    EVERY_N_SECONDS(5)
    {
        nextPalette();
    }
    EVERY_N_MILLISECONDS(40)
    {
        nblendPaletteTowardPalette(currentPalette, targetPalette, 24);
    }
    //  randomGame();
    EVERY_N_MILLIS(patternInterval)
    {
        patternsStripe[CurrentStripePatternNumber].drawFrame();
        //  FastLED[2].showLeds(overAllBrightness);
    }
    EVERY_N_MILLIS(patternInterval)
    {
        patternsMatrix[CurrentMatrixPatternNumber].drawFrame();
        //  FastLED[0].showLeds(overAllBrightness);
    }

    drawTime(1, 0, CHSV(150, 150, 150), true, true);

    FastLED.show();
    //  FastLED[2].delay(patternInterval);
    FastLED.setBrightness(overAllBrightness);
}
void nextPattern()
{
    preferences.begin("patterns", false);
    CurrentStripePatternNumber >= StripePatternsAmount ? CurrentStripePatternNumber = StripePatternsAmount : CurrentStripePatternNumber++;
    FastLED.clear();
    preferences.putInt("stripePattern", CurrentStripePatternNumber);
    runString(patternsStripe[CurrentStripePatternNumber].name, CRGB::White, 1);
    preferences.end();
}
void prevPattern()
{
    preferences.begin("patterns", false);
    CurrentStripePatternNumber <= 0 ? CurrentStripePatternNumber = 0 : CurrentStripePatternNumber--;
    FastLED.clear();
    preferences.putInt("stripePattern", CurrentStripePatternNumber);
    preferences.end();
}
void nextMatrix()
{
    preferences.begin("patterns", false);
    CurrentMatrixPatternNumber >= MatrixPatternsAmount ? CurrentMatrixPatternNumber = MatrixPatternsAmount : CurrentMatrixPatternNumber++;
    FastLED.clear();
    preferences.putInt("matrixPattern", CurrentMatrixPatternNumber);
    preferences.end();
}
void prevMatrix()
{
    preferences.begin("patterns", false);
    CurrentMatrixPatternNumber <= 0 ? CurrentMatrixPatternNumber = 0 : CurrentMatrixPatternNumber--;
    FastLED.clear();
    preferences.putInt("matrixPattern", CurrentMatrixPatternNumber);
    preferences.end();
}
void setBright(uint8_t bright)
{
    preferences.begin("patterns", false);
    overAllBrightness = bright;
    Serial.println(String(overAllBrightness));
    preferences.putInt("oaBrightness", overAllBrightness);
    preferences.end();
}
void setSpeed(uint16_t speed)
{
    preferences.begin("patterns", false);
    patternInterval = speed;
    Serial.println(String(patternInterval));
    preferences.putInt("patternInterval", patternInterval);
    preferences.end();
}