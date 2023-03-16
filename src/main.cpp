

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
    gCurrentPatternNumber == 7 ? gCurrentPatternNumber = 0 : gCurrentPatternNumber++;
    FastLED.clear();
}

void updatePattern(int pat)
{ // call the pattern currently being created
    switch (pat)
    {
    case 0:
        Enoise();
        break;
    case 1:
        //  displayVURainbow();
        break;
    case 2:
        //  displayVU();
        break;
    case 3:
        //  bpm();
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

void displayVUWhite()
{
    currentPatternName = "VuWhite";
    FastLED.clear();

    for (int i = 0; i < Intensity[0]; i++)
    {
        stripe[i + NUM_LEDS_STRIPE / 2] = CRGB::White;
        stripe[NUM_LEDS_STRIPE / 2 - i] = CRGB::White;
    }
}

void displayVURainbow()
{
    currentPatternName = "VURainbow";
    FastLED.clear();
    for (int i = 0; i < Intensity[0]; i++)
    {
        stripe[i + NUM_LEDS_STRIPE / 2] = CHSV(((i * 256 / 12) + 10 + colorTimer), 255, bright);
        stripe[NUM_LEDS_STRIPE / 2 - i] = CHSV(((i * 256 / 12) + 10 + colorTimer), 255, bright);
    }
    FastLED.show();
}
void displayUpdate()
{
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

void rainbow() // rainbowWithGlitter()//confetti
{
    currentPatternName = "Rainbow";

    static uint16_t j = 0;
    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        stripe[i] = CHSV((i + j), 255, 255);
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
    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    { // 9948
        stripe[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
    FastLED.show();
}

void setup()
{
    Serial.begin(115200);

    FastLED.addLeds<CHIPSET, LED_PIN_MATRIX, COLOR_ORDER>(matrix, NUM_LEDS_MATRIX).setCorrection(TypicalLEDStrip); // Initialize NEO_MATRIX
    FastLED.addLeds<CHIPSET, LED_PIN_STRIPE, COLOR_ORDER>(stripe, NUM_LEDS_STRIPE).setCorrection(TypicalLEDStrip);

    FastLED.setBrightness(255);
    Serial.println("start");
    //   Wire.begin();
    pinMode(AUDIO_IN_PIN, INPUT);
    Serial.println("setup done");
}

void loop()
{

    EVERY_N_MILLISECONDS(500) { colorTimer++; }

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
