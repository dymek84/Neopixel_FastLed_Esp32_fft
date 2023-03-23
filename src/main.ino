

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

void nextPattern()
{
    gCurrentPatternNumber == 3 ? gCurrentPatternNumber = 0 : gCurrentPatternNumber++;
    // FastLED.clear();
    Serial.println("nextPattern();");
}
uint8_t BeatsPerMinute = 62;
void bpm(ledTypeConnected whichLeds)
{
    currentPatternName = "bpm";
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)

    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    if (whichLeds == MATRIXLEDS)
    {
        for (int i = 0; i < NUM_LEDS_MATRIX; i++)
        {
            matrix[i] = ColorFromPalette(currentPalette, gHue + (i * 2), beat - gHue + (i * 10));
        }
    }
    else
    {
        for (int i = 0; i < NUM_LEDS_STRIPE; i++)
        {
            stripe[i] = ColorFromPalette(currentPalette, gHue + (i * 2), beat - gHue + (i * 10));
        }
    }
    FastLED.show();
}
#define SAMPLES2 32 // Must be a power of 2
double vReal2[SAMPLES2];
double vImag2[SAMPLES2];
double vResult2[NUM_LEDS_STRIPE / 2];
int result_vu1;
int result_vu2;
int result_vu3;

void reorg_to_led()
{
    // Reorganize number of spectrum to number leds
    for (int i = 0; i < NUM_LEDS_STRIPE / 2; i++)
    {
        int iteration = map(i, 0, NUM_LEDS_STRIPE / 2, 3, SAMPLES2 - 5);
        vResult2[i] = vReal[iteration];
    }
}

void sampling()
{
    // ++ Sampling
    for (int i = 0; i < SAMPLES2; i++)
    {
        // delay(10);
        int value = analogRead(AUDIO_IN_PIN) - 512; // Read from ADC and subtract DC offset caused value
        vReal2[i] = value / 4;                      // Copy to bins after compressing
        vImag2[i] = 0;
    }
    // -- Sampling
}

void FFT_comp()
{
    // ++ FFT
    FFT.DCRemoval(vReal2, SAMPLES);
    FFT.Windowing(vReal2, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
    FFT.Compute(vReal2, vImag2, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal2, vImag2, SAMPLES);
    // -- FFT
}

void VU_meter()
{
#define chanel 27
    EVERY_N_MILLISECONDS(25)
    {
        analyzeAudio();
    }
    int input_vu1 = constrain(map(vReal[25], 0, 512, 0, NUM_LEDS_STRIPE / 2), 0, 255);
    int input_vu2 = constrain(map(vReal[3], 0, 512, 0, NUM_LEDS_STRIPE / 2), 0, 255);
    int input_vu3 = constrain(map(vReal[16], 0, 512, 0, NUM_LEDS_STRIPE / 2), 0, 255);
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
    //  fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 5);
}

void displayUpdate()
{
    analyzeAudio();
    int color = 0;
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
        for (int j = 0; j < MATRIX_HEIGHT; j++)
        {
            if (j <= Intensity[i])
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

void updatePatternMatrix(int pat)
{ // call the pattern currently being created
    switch (pat)
    {
    case 0:
        Enoise(MATRIXLEDS);
        break;
    case 1:
        displayUpdate();
        break;
    case 2:
        bpm(MATRIXLEDS);
        break;
    case 3:
        break;
    case 4:
        // displayVUWhite();
        break;
    case 5:
        //   rainbow();
        break;
    case 6:
        //    test();
        break;
    case 7:
        //    test2();
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
void updatePatternStripe(int pat)
{ // call the pattern currently being created
    switch (pat)
    {
    case 0:
        VUStripe();
        break;
    case 1:
        rippless();
        break;
    case 2:
        bpm(STRIPELEDS);
        break;
    case 3:
        VU_meter();
        break;
    case 4:
        water_fall_vu();
        break;
    case 5:
        pacifica_loop();
        break;
    case 6:

        fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 64);
        salut();
        FastLED.show();

        break;
    case 7:
        //    test2();
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

void displayVUWhite()
{
    currentPatternName = "VuWhite";
    // FastLED.clear();

    for (int i = 0; i < Intensity[0]; i++)
    {
        stripe[i + NUM_LEDS_STRIPE / 2] = CRGB::White;
        stripe[NUM_LEDS_STRIPE / 2 - i] = CRGB::White;
    }
}

void displayVURainbow()
{
    currentPatternName = "VURainbow";
    // FastLED.clear();
    for (int i = 0; i < Intensity[0]; i++)
    {
        stripe[i + NUM_LEDS_STRIPE / 2] = CHSV(((i * 256 / 12) + 10 + colorTimer), 255, bright);
        stripe[NUM_LEDS_STRIPE / 2 - i] = CHSV(((i * 256 / 12) + 10 + colorTimer), 255, bright);
    }
    FastLED.show();
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
            Serial.print(": ");
            Serial.print("bandValues ");
            Serial.print(bandValues[band]);
            Serial.print(" -> ");
            int barHeight = bandValues[band]; // / 400;
            Serial.print(">>>>>>>>>>>>>>>> ");
            Serial.print("barHeight = bandValues[band] / 400 - >");
            Serial.print(barHeight);
            Serial.print(" <<<<<<<<<<<<<<<<");
            barHeight = map(barHeight, 0, 200, 1, 8);
            Serial.print(barHeight);

            if (barHeight > 255)
                barHeight = 255;
            Serial.print("(");
            Serial.print(barHeight);
            Serial.println(") ");
        }
        Serial.println("__________________________________________________________ ");
        int avrg = 0;

        for (byte band = 0; band < NUM_BANDS; band++)
        {

            int barHeight = bandValues[band]; // / 400;

            barHeight = map(barHeight, 0, 1000, 1, 255);
            if (barHeight > 256)
                barHeight = 256;

            drawOnSerial(barHeight);

            avrg += barHeight;
        }
    }
}

// const uint8_t paletteCount = ARRAY_SIZE(paletteList);
void nextPalette()
{
    currentPaletteIndex = (currentPaletteIndex + 1) % paletteCount;
    targetPalette = paletteList[currentPaletteIndex];
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
void setup()
{
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
           // listDir(SPIFFS, "/", 2);
        }
        // RunWebserver();
        setupSite();
        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = true;
    }
    else
    {
        Serial.println("No WIFI, let's offer an accesspoint");

        //  RunAPmode();

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
    pinMode(AUDIO_IN_PIN, INPUT);
    preferences.end();
    // initWebSocket();
    Serial.println("setup done");
}
// frequency needs to be lower than LED_FREQ_LIM
#define LED_FREQ_LIM 150

// magnitude needs to be greater than 1.15*avgMag
#define LED_MAG_LIM 1.15

// average magnitude is calculated by dividing with avgSampleCount, which is limited to AVG_COUNT_LIMIT
#define AVG_COUNT_LIMIT 500

// once avgSampleCount reaches AVG_COUNT_LIMIT, it gets reset back to AVG_COUNT_LOWER
#define AVG_COUNT_LOWER 100

#define BPM 180

// Define this to use reciprocal multiplication for division and some more speedups that might decrease precision
#define FFT_SPEED_OVER_PRECISION
float magAvg = 0;
int avgSampleCount = 1;

int fade = 0; // fading of leds
double beatTime = 60.0 / BPM * 1000;

float freq, mag;    // peak frequency and magnitude
float lastBeat = 0; // time of last beat in millis()
void loop()
{
    loopSite();
    /// ws.cleanupClients();
    EVERY_N_MILLISECONDS(500) { colorTimer++; }
    EVERY_N_SECONDS(5)
    {
        nextPalette();
    }
    EVERY_N_MILLISECONDS(40)
    {
        nblendPaletteTowardPalette(currentPalette, targetPalette, 24);
    }
    EVERY_N_SECONDS(20)
    {
        nextPattern();

        Serial.print(currentPatternName);
        Serial.print(" - number: ");
        Serial.println(gCurrentPatternNumber);

    } // change patterns periodically
    updatePatternMatrix(gCurrentPatternNumber);
    // updatePatternStripe(6);
    uint8_t delay = patterns[StripePatternIndex].drawFrame();

    // send the 'leds' array out to the actual LED strip
    FastLED.show();

    // insert a delay to keep the framerate modest
    FastLED.delay(delay);
}
