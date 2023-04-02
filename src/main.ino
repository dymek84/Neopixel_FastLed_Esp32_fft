

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
double vResult2[NUM_LEDS_STRIPE / 2];
int result_vu1;
int result_vu2;
int result_vu3;

void VU_meter()
{
#define chanel 27
    EVERY_N_MILLISECONDS(25)
    {
        analyzeAudio();
    }
    int input_vu1 = constrain(map(bandValues[25], 0, 3000, 0, NUM_LEDS_STRIPE / 2), 0, 255);
    int input_vu2 = constrain(map(bandValues[3], 0, 3000, 0, NUM_LEDS_STRIPE / 2), 0, 255);
    int input_vu3 = constrain(map(bandValues[16], 0, 3000, 0, NUM_LEDS_STRIPE / 2), 0, 255);
    Serial.println(input_vu1);
    Serial.println(input_vu2);
    Serial.println(input_vu3);
    Serial.println();
    if (result_vu1 < input_vu1)
    {
        result_vu1 = result_vu1 + ((input_vu1 - result_vu1) * .5); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
    }
    else
    {
        result_vu1 = result_vu1 - ((result_vu1 - input_vu1) * .8); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
    }
    if (result_vu2 < input_vu2)
    {
        result_vu2 = result_vu2 + ((input_vu2 - result_vu2) * .5); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
    }
    else
    {
        result_vu2 = result_vu2 - ((result_vu2 - input_vu2) * .8); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
    }
    if (result_vu3 < input_vu3)
    {
        result_vu3 = result_vu3 + ((input_vu3 - result_vu3) * .5); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
    }
    else
    {
        result_vu3 = result_vu3 - ((result_vu3 - input_vu3) * .8); //((map(vReal[chanel],0,512,0,NUM_LEDS/2)-result_vu)/2);
    }
    FOR_i(0, NUM_LEDS_STRIPE / 4)
    {
        if (result_vu1 > i)
        {
            stripe[(NUM_LEDS_STRIPE / 2) - i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 255);
            stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 255);
        }
        else
        {
            stripe[(NUM_LEDS_STRIPE / 2) - i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
            stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
        }
        if (result_vu2 > i)
        {
            stripe[(NUM_LEDS_STRIPE)-i - 1] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 255);
            // stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 255);
        }
        else
        {
            stripe[(NUM_LEDS_STRIPE)-i - 1] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
            // stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
        }
        if (result_vu3 > i)
        {
            stripe[i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 255);
            // stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 255);
        }
        else
        {
            stripe[i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
            //  stripe[(NUM_LEDS_STRIPE / 2) + i] = CHSV(beatsin8(3, 0, 255, 0, i), 255, 0);
        }
    }
    FastLED.show();
    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 150);
}

void displayUpdate()
{
    // analyzeAudio();
    int color = 0;
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
        for (int j = 0; j < MATRIX_HEIGHT; j++)
        {
            if (j <= bandValues[i])
            { // Light everything within the intensity range
                if (j % 2 == 0)
                {
                    matrix[((MATRIX_WIDTH * (j + 1)) - i - 1)] = CHSV(color, 255, bright);
                    matrix[255 - ((MATRIX_WIDTH * (j + 1)) - i - 1)] = CHSV(color, 255, bright);
                }
                else
                {
                    matrix[((MATRIX_WIDTH * j) + i)] = CHSV(color, 255, bright);
                    matrix[255 - ((MATRIX_WIDTH * j) + i)] = CHSV(color, 255, bright);
                }
            }
            else
            { // Everything outside the range goes dark
                if (j % 2 == 0)
                {
                    matrix[((MATRIX_WIDTH * (j + 1)) - i - 1)] = CHSV(color, 255, 0);
                    matrix[255 - ((MATRIX_WIDTH * (j + 1)) - i - 1)] = CHSV(color, 255, 0);
                }
                else
                {
                    matrix[((MATRIX_WIDTH * j) + i)] = CHSV(color, 255, 0);
                    matrix[255 - ((MATRIX_WIDTH * j) + i)] = CHSV(color, 255, 0);
                }
            }
        }
        color += 255 / MATRIX_WIDTH; // Increment the Hue to get the Rainbow
    }
    FastLED.show();
}

void displayVUWhite()
{

    for (int i = 0; i < bandValues[0]; i++)
    {
        stripe[i + NUM_LEDS_STRIPE / 2] = CRGB::White;
        stripe[NUM_LEDS_STRIPE / 2 - i] = CRGB::White;
    }
}

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

    FastLED.setBrightness(255);
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
    pinMode(MIC_IN_PIN, INPUT);
    preferences.end();
    Serial.println("preferences.end");
    setupWebServer();
    sampling_period_us = (1.0 / SAMPLING_FREQ) * pow(10.0, 6);

    syncTime();
    Serial.println("setup done");
}

void loop()
{
    RtcDateTime now = Rtc.GetDateTime();

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
    patternsStripe[CurrentStripePatternNumber].drawFrame();
    patternsMatrix[CurrentMatrixPatternNumber].drawFrame();
    // backgroundVuMatrix();
    //  matrixSpectrum();
    // Wave();

    setNum(now.Hour() / 10, 0);   // set first digit of hour
    setNum(now.Hour() % 10, 1);   // set second digit of hour
    setNum(now.Minute() / 10, 2); // set first digit of hour
    setNum(now.Minute() % 10, 3); // set second digit of hour
    FastLED.show();
}
void nextPattern()
{
    CurrentStripePatternNumber >= StripePatternsAmount ? CurrentStripePatternNumber = StripePatternsAmount : CurrentStripePatternNumber++;
}
void prevPattern()
{
    CurrentStripePatternNumber <= 0 ? CurrentStripePatternNumber = 0 : CurrentStripePatternNumber--;
}
void nextMatrix()
{
    CurrentMatrixPatternNumber >= MatrixPatternsAmount ? CurrentMatrixPatternNumber = MatrixPatternsAmount : CurrentMatrixPatternNumber++;
}
void prevMatrix()
{
    CurrentMatrixPatternNumber <= 0 ? CurrentMatrixPatternNumber = 0 : CurrentMatrixPatternNumber--;
}
