
#include <Arduino.h>
#include <arduinoFFT.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <DS1307RTC.h>
#include "clock.cpp"
#include "ripple.cpp"
#include "buttons.cpp"

boolean showMenu = false;
boolean moreTime = false;
int menuname = 0;
int percentage = 0;
int COLORS = 255;
int stripeBrightness = 10;
int clockBright = 125;
unsigned long patternInterval = 0;

//////////////////////   MATRIX   /////////////////////////
#define SAMPLES 16 // Must be a power of 2 (64)
#define LED_PIN 4  // Data pin to LEDS
#define NUM_LEDS 256
#define MULTIPLY_BY 3
#define BRIGHTNESS 125 // LED information
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BUTTON_PIN 3
#define xres 8  // Total number of  columns in the display
#define yres 16 // Total number of  rows in the display

double vReal[SAMPLES];
double vImag[SAMPLES];

int Intensity[xres] = {}; // initialize Frequency Intensity to zero
int Displacement = 1;

CRGB matrix[NUM_LEDS];
CRGB firstStripe[15];          // Create LED Object
arduinoFFT FFT = arduinoFFT(); // Create FFT object
//////////////////////   MATRIX END  /////////////////////////

int selected = 5;
int counter = 5;

int longstrip = 15;         // 86;
int shortstrip = 15;        // 80;
int longerstrip = 15;       // 88;
#define allPixelsAmount 181 // 988 //= longstrip * 2 + longerstrip * 2 + shortstrip * 8;
int halfofPixels = allPixelsAmount / 2;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(longstrip, 13, NEO_GRB + NEO_KHZ800);   // 86 pixels
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(shortstrip, 14, NEO_GRB + NEO_KHZ800);  // 80 pixels
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(shortstrip, 27, NEO_GRB + NEO_KHZ800);  // 80 pixels
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(shortstrip, 26, NEO_GRB + NEO_KHZ800);  // 80 pixels
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(shortstrip, 25, NEO_GRB + NEO_KHZ800);  // 80 pixels
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(longerstrip, 32, NEO_GRB + NEO_KHZ800); // 88 pixels
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(longerstrip, 23, NEO_GRB + NEO_KHZ800); // 88 pixels
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(shortstrip, 15, NEO_GRB + NEO_KHZ800);  // 80 pixels
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(shortstrip, 2, NEO_GRB + NEO_KHZ800);   // 80 pixels
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(shortstrip, 19, NEO_GRB + NEO_KHZ800);  // 80 pixels
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(shortstrip, 18, NEO_GRB + NEO_KHZ800); // 80 pixels
Adafruit_NeoPixel strip11 = Adafruit_NeoPixel(longstrip, 5, NEO_GRB + NEO_KHZ800);   // 86 pixels

uint32_t red = pixels.Color(255, 0, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t white = pixels.Color(255, 255, 255);
uint32_t pink = pixels.Color(255, 0, 100);
uint32_t cyan = pixels.Color(0, 255, 255);
uint32_t orange = pixels.Color(230, 80, 0);
uint32_t colors[] = {red, orange, yellow, green, cyan, blue, pink};
uint32_t black = pixels.Color(0, 0, 0);

#define GRAVITY -9.81                     // Downward (negative) acceleration of gravity in m/s^2
#define h0 2                              // Starting height, in meters, of the ball (strip length)
#define NUM_BALLS 4                       // Number of bouncing balls you want (recommend < 7, but 20 is fun in its own way)
#define SPEED .20                         // Amount to increment RGB color by each cycle
float h[NUM_BALLS];                       // An array of heights
float vImpact0 = sqrt(-2 * GRAVITY * h0); // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
float vImpact[NUM_BALLS];                 // As time goes on the impact velocity will change, so make an array to store those values
float tCycle[NUM_BALLS];                  // The time since the last time the ball struck the ground
int pos[NUM_BALLS];                       // The integer position of the dot on the strip (LED index)
long tLast[NUM_BALLS];                    // The clock time of the last ground strike
float COR[NUM_BALLS];                     // Coefficient of Restitution (bounce damping)
tmElements_t tm;
#define audio A0
void clock(int hour, int min);
void buttons();

const int sampleWindow = 1;   // Sample window width in mS (50 mS = 20Hz)
const int sampleWindow1 = 10; // Sample window width in mS (50 mS = 20Hz)
int maximum = 110;
int maximum1 = 110;
int peak;
int peak1;
int dotCount;
int dotCount1;
unsigned int sample;
unsigned int sample1;
bool gReverseDirection = false;
#define COLOR_FROM 0
#define COLOR_TO 255
#define COLOR_START 0
#define PEAK_FALL 4  // Rate of peak falling dot
#define PEAK_FALL1 4 // Rate of peak falling dot
Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(32, 8, LED_PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);
const uint16_t colors2[] = {matrix2.Color(0, 255, 0), matrix2.Color(255, 255, 0), matrix2.Color(0, 0, 255), matrix2.Color(255, 0, 255), matrix2.Color(0, 255, 255), matrix2.Color(255, 255, 255)};

int x2 = matrix2.width();
int pass = 0;
void scrollText()
{
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
            matrix2.setTextColor(colors2[pass]);
        }
        matrix2.show();
        delay(20);
    }
    delay(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{

    delay(3000);

    Serial.begin(115200); // Initialize Serial
    randomSeed(analogRead(A0));
    selected = EEPROM.read(0);
    counter = selected;
    stripeBrightness = EEPROM.read(1);
    COLORS = EEPROM.read(2);
    patternInterval = EEPROM.read(3);
    clockBright = EEPROM.read(4);
    pinMode(audio, INPUT);

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(matrix, NUM_LEDS).setCorrection(TypicalLEDStrip); // Initialize LED strips
    FastLED.addLeds<LED_TYPE, 23, COLOR_ORDER>(firstStripe, 15).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(clockBright);

    pixels.begin();
    strip1.begin();
    strip2.begin();
    strip3.begin();
    strip4.begin();
    strip5.begin();
    strip6.begin();
    strip7.begin();
    strip8.begin();
    strip9.begin();
    strip10.begin();
    strip11.begin();
    setBrightness(stripeBrightness);
    ////////////////////////// MATRIX TEXT SCROLL //////////////////////////
    matrix2.begin();
    matrix2.setTextWrap(false);
    matrix2.setBrightness(clockBright);
    matrix2.setTextColor(colors2[0]);
    scrollText();
    //------------------------ MATRIX TEXT SCROLL ----------------------
    intro();
    AllOff();

    for (int i = 0; i < NUM_BALLS; i++)
    {
        tLast[i] = millis();
        h[i] = h0;
        pos[i] = 0;            // Balls start on the ground
        vImpact[i] = vImpact0; // And "pop" up at vImpact0
        tCycle[i] = 0;
        COR[i] = 0.90 - float(i) / pow(NUM_BALLS, 2);
    }
}

void loop()
{
    RTC.read(tm);
    buttons();
    Visualizer();

    unsigned long currentMillis = millis();

    setBrightness(stripeBrightness);

    updatePattern(selected);
}
unsigned long startTime = 0;
boolean timing = false;
unsigned long timeOut = 5000;

byte inputState = HIGH;
byte lastInputState = HIGH;
void Visualizer()
{
    // Collect Samples
    getSamples();
    // Update Display

    displayUpdate();
    buttons();
    // inputState = digitalRead(modeButtonSelect);
    if (showMenu == false)
    {
        clock(tm.Hour, tm.Minute, false, 0, 0);
        moreTime = false;
        startTime = millis();
    }
    else if (showMenu == true)
    {
        clock(counter, selected, true, menuname, percentage);
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
    }
    FastLED.show();
}

long previousMillisa = 0;

void getSamples()
{
    for (int i = 0; i < SAMPLES; i++)
    {
        vReal[i] = analogRead(audio) * MULTIPLY_BY;
        // Serial.print(i);
        // Serial.print(" - ");
        //  Serial.println(vReal[i]);
        vImag[i] = 0;
    }

    // FFT
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    // Update Intensity Array
    for (int i = 2; i < (xres * Displacement) + 2; i += Displacement)
    {
        vReal[i] = constrain(vReal[i], 0, 2047);    // set max value for input data
        vReal[i] = map(vReal[i], 0, 2047, 0, yres); // map data to fit our display

        Intensity[(i / Displacement) - 2]--;              // Decrease displayed value
        if (vReal[i] > Intensity[(i / Displacement) - 2]) // Match displayed value to measured value
            Intensity[(i / Displacement) - 2] = vReal[i];
    }
}
void displayVU()
{

    AllOff();
    for (int i = 0; i < Intensity[0]; i++)
    {
        pixels.setPixelColor(i + longstrip / 2, colors[0]);
        pixels.setPixelColor(longstrip / 2 - i, colors[0]);
    }
    for (int i = 0; i < Intensity[1]; i++)
    {
        strip1.setPixelColor(i + shortstrip / 2, colors[1]);
        strip1.setPixelColor(shortstrip / 2 - i, colors[1]);
    }
    for (int i = 0; i < Intensity[2]; i++)
    {
        strip2.setPixelColor(i + shortstrip / 2, colors[2]);
        strip2.setPixelColor(shortstrip / 2 - i, colors[2]);
    }
    for (int i = 0; i < Intensity[3]; i++)
    {
        strip3.setPixelColor(i + shortstrip / 2, colors[3]);
        strip3.setPixelColor(shortstrip / 2 - i, colors[3]);
    }
    for (int i = 0; i < Intensity[4]; i++)
    {
        strip4.setPixelColor(i + shortstrip / 2, colors[4]);
        strip4.setPixelColor(shortstrip / 2 - i, colors[4]);
    }
    for (int i = 0; i < Intensity[5]; i++)
    {
        strip5.setPixelColor(i + longerstrip / 2, colors[5]);
        strip5.setPixelColor(longerstrip / 2 - i, colors[5]);
    }
    for (int i = 0; i < Intensity[5]; i++)
    {
        strip6.setPixelColor(i + longerstrip / 2, colors[5]);
        strip6.setPixelColor(longerstrip / 2 - i, colors[5]);
    }
    for (int i = 0; i < Intensity[4]; i++)
    {
        strip7.setPixelColor(i + shortstrip / 2, colors[4]);
        strip7.setPixelColor(shortstrip / 2 - i, colors[4]);
    }
    for (int i = 0; i < Intensity[3]; i++)
    {
        strip8.setPixelColor(i + shortstrip / 2, colors[3]);
        strip8.setPixelColor(shortstrip / 2 - i, colors[3]);
    }
    for (int i = 0; i < Intensity[2]; i++)
    {
        strip9.setPixelColor(i + shortstrip / 2, colors[2]);
        strip9.setPixelColor(shortstrip / 2 - i, colors[2]);
    }
    for (int i = 0; i < Intensity[1]; i++)
    {
        strip10.setPixelColor(i + shortstrip / 2, colors[1]);
        strip10.setPixelColor(shortstrip / 2 - i, colors[1]);
    }
    for (int i = 0; i < Intensity[0]; i++)
    {
        strip11.setPixelColor(i + longstrip / 2, colors[0]);
        strip11.setPixelColor(longstrip / 2 - i, colors[0]);
    }
    showAllStrips();
}
// #define PEAK_FALL 5 // Rate of peak falling dot
// byte peak = 0; // Used for falling dot
void displayVUWhite()
{
    if (Intensity[0] > peak)
        peak = Intensity[0]; // Keep 'peak' dot at top
    if (peak > 0 && peak <= 15 - 1)
    {
        pixels.setPixelColor(peak, white);
    }
    if (++dotCount >= PEAK_FALL)
    { // fall rate

        if (peak > 0)
            peak--;
        dotCount = 0;
    }
    AllOff();
    for (int i = 0; i < Intensity[0]; i++)
    {
        pixels.setPixelColor(i + longstrip / 2, white);
        pixels.setPixelColor(longstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[1]; i++)
    {
        strip1.setPixelColor(i + shortstrip / 2, white);
        strip1.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[2]; i++)
    {
        strip2.setPixelColor(i + shortstrip / 2, white);
        strip2.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[3]; i++)
    {
        strip3.setPixelColor(i + shortstrip / 2, white);
        strip3.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[4]; i++)
    {
        strip4.setPixelColor(i + shortstrip / 2, white);
        strip4.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[5]; i++)
    {
        strip5.setPixelColor(i + longerstrip / 2, white);
        strip5.setPixelColor(longerstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[5]; i++)
    {
        strip6.setPixelColor(i + longerstrip / 2, white);
        strip6.setPixelColor(longerstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[4]; i++)
    {
        strip7.setPixelColor(i + shortstrip / 2, white);
        strip7.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[3]; i++)
    {
        strip8.setPixelColor(i + shortstrip / 2, white);
        strip8.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[2]; i++)
    {
        strip9.setPixelColor(i + shortstrip / 2, white);
        strip9.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[1]; i++)
    {
        strip10.setPixelColor(i + shortstrip / 2, white);
        strip10.setPixelColor(shortstrip / 2 - i, white);
    }
    for (int i = 0; i < Intensity[0]; i++)
    {
        strip11.setPixelColor(i + longstrip / 2, white);
        strip11.setPixelColor(longstrip / 2 - i, white);
    }
    showAllStrips();
}
int countplus = 0;
void displayVURainbow()
{

    AllOff();
    for (int i = 0; i < Intensity[0]; i++)
    {
        pixels.setPixelColor(i + longstrip / 2, Wheel(((i * 256 / 12) + 10 + countplus) & 255, 1));
        pixels.setPixelColor(longstrip / 2 - i, Wheel(((i * 256 / 12) + 10 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[1]; i++)
    {
        strip1.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 20 + countplus) & 255, 1));
        strip1.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 20 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[2]; i++)
    {
        strip2.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 30 + countplus) & 255, 1));
        strip2.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 30 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[3]; i++)
    {
        strip3.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 40 + countplus) & 255, 1));
        strip3.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 40 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[4]; i++)
    {
        strip4.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 50 + countplus) & 255, 1));
        strip4.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 50 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[5]; i++)
    {
        strip5.setPixelColor(i + longerstrip / 2, Wheel(((i * 256 / 12) + 60 + countplus) & 255, 1));
        strip5.setPixelColor(longerstrip / 2 - i, Wheel(((i * 256 / 12) + 60 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[5]; i++)
    {
        strip6.setPixelColor(i + longerstrip / 2, Wheel(((i * 256 / 12) + 70 + countplus) & 255, 1));
        strip6.setPixelColor(longerstrip / 2 - i, Wheel(((i * 256 / 12) + 70 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[4]; i++)
    {
        strip7.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 80 + countplus) & 255, 1));
        strip7.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 80 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[3]; i++)
    {
        strip8.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 90 + countplus) & 255, 1));
        strip8.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 90 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[2]; i++)
    {
        strip9.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 100 + countplus) & 255, 1));
        strip9.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 100 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[1]; i++)
    {
        strip10.setPixelColor(i + shortstrip / 2, Wheel(((i * 256 / 12) + 110 + countplus) & 255, 1));
        strip10.setPixelColor(shortstrip / 2 - i, Wheel(((i * 256 / 12) + 110 + countplus) & 255, 1));
    }
    for (int i = 0; i < Intensity[0]; i++)
    {
        strip11.setPixelColor(i + longstrip / 2, Wheel(((i * 256 / 12) + 120 + countplus) & 255, 1));
        strip11.setPixelColor(longstrip / 2 - i, Wheel(((i * 256 / 12) + 120 + countplus) & 255, 1));
    }
    showAllStrips();
    countplus == 255 ? countplus = 0 : countplus += 5;
}
void displayUpdate()
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
                    matrix[((xres * (j + 1)) - i - 1)] = CHSV(color, 255, clockBright);
                    matrix[255 - ((xres * (j + 1)) - i - 1)] = CHSV(color, 255, clockBright);
                }
                else
                {
                    matrix[((xres * j) + i)] = CHSV(color, 255, clockBright);
                    matrix[255 - ((xres * j) + i)] = CHSV(color, 255, clockBright);
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
}

void updatePattern(int pat)
{ // call the pattern currently being created
    switch (pat)
    {
    case 0:
        Balls();
        break;
    case 1:
        strobo();
        break;
    case 2:
        around();
        break;
    case 3:
        Twinkle();
        break;
    case 4:
        vu3();
        break;
    case 5:
        ripple();
        break;
    case 6:
        rainbowCycle();
        break;
    case 7:
        color();
        break;
    case 8:
        vutest();
        break;
    case 9:
        vutest();
        break;
    case 10:
        fill();
        break;
    case 11:
        fillCenter();
        break;
    case 12:
        displayVU();
        break;
    case 13:
        displayVUWhite();
        break;
    case 14:
        displayVURainbow();
        break;
    case 15:
        theaterChaseRainbow();
        break;
    case 16:
        theaterChase();
        break;
    }
}

void AllOff()
{
    pixels.clear();
    pixels.show();
    strip1.clear();
    strip1.show();
    strip2.clear();
    strip2.show();
    strip3.clear();
    strip3.show();
    strip4.clear();
    strip4.show();
    strip5.clear();
    strip5.show();
    strip6.clear();
    strip6.show();
    strip7.clear();
    strip7.show();
    strip8.clear();
    strip8.show();
    strip9.clear();
    strip9.show();
    strip10.clear();
    strip10.show();
    strip11.clear();
    strip11.show();
}
void AllStripSame(int i, uint32_t color)
{
    pixels.setPixelColor(i, color);
    strip1.setPixelColor(i, color);
    strip2.setPixelColor(i, color);
    strip3.setPixelColor(i, color);
    strip4.setPixelColor(i, color);
    strip5.setPixelColor(i, color);
    strip6.setPixelColor(i, color);
    strip7.setPixelColor(i, color);
    strip8.setPixelColor(i, color);
    strip9.setPixelColor(i, color);
    strip10.setPixelColor(i, color);
    strip11.setPixelColor(i, color);
}
uint32_t Wheel(byte WheelPos, float opacity)
{

    if (WheelPos < 85)
    {
        return pixels.Color((WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return pixels.Color((255 - WheelPos * 3) * opacity, 0, (WheelPos * 3) * opacity);
    }
    else
    {
        WheelPos -= 170;
        return pixels.Color(0, (WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity);
    }
}
// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}
// pixels.Color(r, g, b));
void SetMyLED(int i, int r, int g, int b)
{

    if (i <= longstrip - 1) // 1
    {
        pixels.setPixelColor(longstrip - 1 - i, pixels.Color(r, g, b));
        //   pixels.show();
    }
    else if (i <= (longstrip + shortstrip) && i > longstrip) // 2
    {
        strip1.setPixelColor(i - longstrip - 1, pixels.Color(r, g, b));
        //   strip1.show();
    }
    else if (i < (longstrip + shortstrip * 2) + 1 && i >= (shortstrip + longstrip)) // 3
    {
        strip2.setPixelColor((longstrip + shortstrip * 2) - i, pixels.Color(r, g, b));
        //    strip2.show();
    }
    else if (i <= (longstrip + shortstrip * 3) && i > (longstrip + shortstrip * 2)) // 4
    {
        strip3.setPixelColor(i - (longstrip + shortstrip * 2) - 1, pixels.Color(r, g, b));
        //     strip3.show();
    }
    else if (i < (longstrip + shortstrip * 4) + 1 && i >= (shortstrip * 3 + longstrip)) // 5
    {
        strip4.setPixelColor((longstrip + shortstrip * 4) - i, pixels.Color(r, g, b));
        //   strip4.show();
    }
    else if (i <= (longstrip + longerstrip + shortstrip * 4) && i > (longstrip + shortstrip * 4)) // 6
    {
        strip5.setPixelColor(i - (longstrip + shortstrip * 4) - 1, pixels.Color(r, g, b));
        //   strip5.show();
    }
    else if (i < (longerstrip * 2 + longstrip + shortstrip * 4) + 1 && i >= (shortstrip * 4 + longstrip + longstrip)) // 7
    {
        strip6.setPixelColor((longstrip + shortstrip * 4 + longerstrip * 2) - i, pixels.Color(r, g, b));
        //   strip6.show();
    }
    else if (i <= (longstrip + longerstrip * 2 + shortstrip * 5) && i > (longstrip + longerstrip * 2 + shortstrip * 4)) // 8
    {
        strip7.setPixelColor(i - (longstrip + longerstrip * 2 + shortstrip * 4) - 1, pixels.Color(r, g, b));
        //   strip7.show();
    }
    else if (i < (longerstrip * 2 + longstrip + shortstrip * 6) + 1 && i >= (shortstrip * 6 + longstrip + longstrip)) // 9
    {
        strip8.setPixelColor((longstrip + longerstrip * 2 + shortstrip * 6) - i, pixels.Color(r, g, b));
        //     strip8.show();
    }
    else if (i <= (longstrip + longerstrip * 2 + shortstrip * 7) && i > (longstrip + longerstrip * 2 + shortstrip * 6)) // 10
    {
        strip9.setPixelColor(i - (longstrip + longerstrip * 2 + shortstrip * 6) - 1, pixels.Color(r, g, b));
        //    strip9.show();
    }
    else if (i < (longerstrip * 2 + longstrip + shortstrip * 8) + 1 && i >= (shortstrip * 7 + longerstrip * 2 + longstrip)) // 11
    {
        strip10.setPixelColor((longstrip + longerstrip * 2 + shortstrip * 8) - i, pixels.Color(r, g, b));
        //    strip10.show();
    }
    else if (i < (longstrip * 2 + longerstrip * 2 + shortstrip * 8) + 1 && i > (longstrip + longerstrip * 2 + shortstrip * 8)) // 12
    {
        strip11.setPixelColor(i - (longstrip + longerstrip * 2 + shortstrip * 8) - 1, pixels.Color(r, g, b));
        //   strip11.show();
    }
}
void SetLeftStripe(int i, uint32_t color)
{
    SetMyLED(halfofPixels + i, color);
}
void SetRightStripe(int i, uint32_t color)
{
    SetMyLED(halfofPixels - i, color);
}
void SetLeftCenterDouble(int i, uint32_t color)
{
    int centerNumber = longstrip + shortstrip + shortstrip;
    SetMyLED(centerNumber - i + 1, color);
    SetMyLED(centerNumber + i, color);
}
void SetRightCenterDouble(int i, uint32_t color)
{
    int centerNumber = longstrip + shortstrip + shortstrip;
    SetMyLED(centerNumber + halfofPixels - i + 1, color);
    SetMyLED(centerNumber + halfofPixels + i, color);
}

void SetMyLED(int i, uint32_t color)
{
    if (i <= longstrip - 1) // 1
    {
        pixels.setPixelColor(longstrip - 1 - i, color);
        //   pixels.show();
    }
    else if (i <= (longstrip + shortstrip) && i > longstrip) // 2
    {
        strip1.setPixelColor(i - longstrip - 1, color);
        //   strip1.show();
    }
    else if (i < (longstrip + shortstrip * 2) + 1 && i >= (shortstrip + longstrip)) // 3
    {
        strip2.setPixelColor((longstrip + shortstrip * 2) - i, color);
        //    strip2.show();
    }
    else if (i <= (longstrip + shortstrip * 3) && i > (longstrip + shortstrip * 2)) // 4
    {
        strip3.setPixelColor(i - (longstrip + shortstrip * 2) - 1, color);
        //     strip3.show();
    }
    else if (i < (longstrip + shortstrip * 4) + 1 && i >= (shortstrip * 3 + longstrip)) // 5
    {
        strip4.setPixelColor((longstrip + shortstrip * 4) - i, color);
        //   strip4.show();
    }
    else if (i <= (longstrip + longerstrip + shortstrip * 4) && i > (longstrip + shortstrip * 4)) // 6
    {
        strip5.setPixelColor(i - (longstrip + shortstrip * 4) - 1, color);
        //   strip5.show();
    }
    else if (i < (longerstrip * 2 + longstrip + shortstrip * 4) + 1 && i >= (shortstrip * 4 + longstrip + longstrip)) // 7
    {
        strip6.setPixelColor((longstrip + shortstrip * 4 + longerstrip * 2) - i, color);
        //   strip6.show();
    }
    else if (i <= (longstrip + longerstrip * 2 + shortstrip * 5) && i > (longstrip + longerstrip * 2 + shortstrip * 4)) // 8
    {
        strip7.setPixelColor(i - (longstrip + longerstrip * 2 + shortstrip * 4) - 1, color);
        //   strip7.show();
    }
    else if (i < (longerstrip * 2 + longstrip + shortstrip * 6) + 1 && i >= (shortstrip * 6 + longstrip + longstrip)) // 9
    {
        strip8.setPixelColor((longstrip + longerstrip * 2 + shortstrip * 6) - i, color);
        //     strip8.show();
    }
    else if (i <= (longstrip + longerstrip * 2 + shortstrip * 7) && i > (longstrip + longerstrip * 2 + shortstrip * 6)) // 10
    {
        strip9.setPixelColor(i - (longstrip + longerstrip * 2 + shortstrip * 6) - 1, color);
        //    strip9.show();
    }
    else if (i < (longerstrip * 2 + longstrip + shortstrip * 8) + 1 && i >= (shortstrip * 7 + longerstrip * 2 + longstrip)) // 11
    {
        strip10.setPixelColor((longstrip + longerstrip * 2 + shortstrip * 8) - i, color);
        //    strip10.show();
    }
    else if (i < (longstrip * 2 + longerstrip * 2 + shortstrip * 8) + 1 && i > (longstrip + longerstrip * 2 + shortstrip * 8)) // 12
    {
        strip11.setPixelColor(i - (longstrip + longerstrip * 2 + shortstrip * 8) - 1, color);
        //   strip11.show();
    }
}
uint16_t getColorofpixel(int i)
{
    if (i <= 7)
    {
        return pixels.getPixelColor(7 - i);
    }
    else if (i < 15 && i > 7)
    {
        return strip1.getPixelColor(i - 8);
    }
    else if (i < 22 && i >= 15)
    {
        return strip2.getPixelColor(21 - i);
    }
    else if (i < 29 && i >= 22)
    {
        return strip3.getPixelColor(i - 22);
    }
    else if (i < 36 && i >= 29)
    {
        return strip4.getPixelColor(35 - i);
    }
    else if (i < 43 && i >= 36)
    {
        return strip5.getPixelColor(i - 36);
    }

    else if (i < 50 && i >= 43)
    {
        return strip6.getPixelColor(49 - i);
    }
    else if (i < 57 && i >= 50)
    {
        return strip7.getPixelColor(i - 50);
    }

    else if (i < 64 && i >= 57)
    {
        return strip8.getPixelColor(63 - i);
    }
    else if (i < 71 && i >= 64)
    {
        return strip9.getPixelColor(i - 64);
    }

    else if (i < 78 && i >= 71)
    {
        return strip10.getPixelColor(77 - i);
    }
    else if (i < 85 && i >= 78)
    {
        return strip11.getPixelColor(i - 78);
    }
}
void setBrightness(int bNum)
{
    strip1.setBrightness(bNum);
    strip2.setBrightness(bNum);
    strip3.setBrightness(bNum);
    strip4.setBrightness(bNum);
    strip5.setBrightness(bNum);
    strip6.setBrightness(bNum);
    strip7.setBrightness(bNum);
    strip8.setBrightness(bNum);
    strip9.setBrightness(bNum);
    strip10.setBrightness(bNum);
    strip11.setBrightness(bNum);
    pixels.setBrightness(bNum);

    pixels.show();
    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
}
void showAllStrips()
{
    pixels.show();
    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
}
long previousMillis = 0;
int aa = 1;
void around()
{
    // AllOff();
    int white;
    int amount = 15;
    unsigned long currentMillis = millis(); // Start of sample window
                                            // if (currentMillis - previousMillis > patternInterval)
    //    {
    if (aa == allPixelsAmount + 13)
    {
        aa = 1;
    }
    // int EyeSize = 4;
    // int red = 255;
    // int blue = 0;
    // int green = 0;
    //  for (int i = 0; i < 85; i++) {
    //  setAll(0,0,0);

    SetMyLED(aa, 255, 255, 255);
    SetMyLED(aa - 1, 0, 0, 0);
    SetMyLED(aa - 2, 255, 255, 255);
    SetMyLED(aa - 3, 0, 0, 0);

    SetMyLED(aa - 10, 255, 255, 255);
    SetMyLED(aa - 11, 0, 0, 0);
    SetMyLED(aa - 12, 255, 255, 255);
    SetMyLED(aa - 13, 0, 0, 0);
    // for (int i = 3; i < amount; i++)
    // {

    //     SetMyLED(aa - i, 0, 255, 0);
    // }
    // SetMyLED(aa - 5, 0, 0, 0);
    showAllStrips();
    // AllOff();
    // SetMyLED(aa + 3, 255, 0, 0);
    //  for (int j = 1; j <= EyeSize; j++) {
    //      SetMyLED(i + j, red, green, blue);
    //    }>
    //  SetMyLED(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    // showStrip();
    // delay(SpeedDelay);
    if (patternInterval > 150)
    {
    }
    else
    {
        aa++;
    }

    previousMillis = currentMillis; // Remember the time
                                    //   }
    //}
}
static boolean one = true;
void strobo()
{
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {

        if (one)
        {
            for (int i = 0; i < allPixelsAmount; i++)
            {
                SetMyLED(i, 255, 255, 255);
            }
        }
        else
        {
            for (int i = 0; i < allPixelsAmount; i++)
            {
                SetMyLED(i, 0, 0, 0);
            }
        }
        one = !one;
        previousMillis = currentMillis; // Remember the time
    }
    // toggel pixelse on or off for next time
    showAllStrips(); //  strip.show(); // display
}

int ai = 0;
int bi = 254;
int aas = random(180);
void Twinkle()
{

    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        if (getColorofpixel(aas) == black)
        {

            SetMyLED(aas, ai, ai, ai);
            showAllStrips();
            ai += 10;
            if (ai >= 255)
            {
                aas = random(180);
                ai = 0;
                Serial.println(getColorofpixel(aa));
            }
        }
        else
        {

            SetMyLED(aas, bi, bi, bi);
            showAllStrips();
            bi--;
            if (bi <= 0)
            {
                aas = random(180);
                bi = 255;
                Serial.println("b");
            }
        }

        previousMillis = currentMillis; // Remember the time
    }
}
void intro()
{
    for (int i = 0; i < 88; i++)
    {

        AllStripSame(i, 255);
        showAllStrips();
        delay(50);
    }
}

void theaterChase()
{                                           // modified from Adafruit example to make it a state machine
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        static int j = 0, q = 0;
        static boolean on = true;
        if (on)
        {
            for (int i = 0; i < allPixelsAmount; i = i + 3)
            {
                SetMyLED(i + q, 255, 255, 255); // turn every third pixel on
                                                /// SetMyLED(i + q, Wheel((i + j) % 255, 1));
            }
        }
        else
        {
            for (int i = 0; i < allPixelsAmount; i = i + 3)
            {
                SetMyLED(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
        on = !on;        // toggel pixelse on or off for next time
        showAllStrips(); //  strip.show(); // display
        q++;             // update the q variable
        if (q >= 3)
        { // if it overflows reset it and update the J variable
            q = 0;
            j++;
            if (j >= 256)
                j = 0;
        }
        previousMillis = currentMillis; // Remember the time
    }
}
void theaterChaseRainbow()
{                                           // modified from Adafruit example to make it a state machine
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        static int j = 0, q = 0;
        static boolean on = true;
        if (on)
        {
            for (int i = 0; i < allPixelsAmount; i = i + 3)
            {
                SetMyLED(i, Wheel(((i * 256 / allPixelsAmount) + j) & 255, 1)); // turn every third pixel on
                                                                                /// SetMyLED(i + q, Wheel((i + j) % 255, 1));
            }
        }
        else
        {
            for (int i = 0; i < allPixelsAmount; i = i + 3)
            {
                SetMyLED(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
        on = !on;        // toggel pixelse on or off for next time
        showAllStrips(); //  strip.show(); // display
        q++;             // update the q variable
        if (q >= 3)
        { // if it overflows reset it and update the J variable
            q = 0;
            j++;
            if (j >= 256)
                j = 0;
        }
        previousMillis = currentMillis; // Remember the time
    }
}
void rainbowCycle()
{                                           // modified from Adafruit example to make it a state machine
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        static uint16_t j = 0;
        for (int i = 0; i < allPixelsAmount; i++)
        {
            SetMyLED(i, Wheel(((i * 256 / allPixelsAmount) + j) & 255, 1));
        }
        showAllStrips();
        j++;
        if (j >= 256 * 5)
            j = 0;
        previousMillis = currentMillis; // time for next change to the display
    }
}
int old = -10;
void color()
{

    // float smooth = 0.8 * smooth + 0.2 * patternInterval;
    // int col = map(smooth, 0, 200, 0, 255);
    int col = map(COLORS, 0, 200, 0, 255);
    if (col - old > 5 || col - old < -5)
    {

        for (int i = 0; i < allPixelsAmount; i++)
        {
            SetMyLED(i, Wheel(col, 1));
        }
        showAllStrips();
        old = col;
    }
}

int outputValue = 0;
int rememberOutputValue;
int randNumber;
int counterss = 0;
int loopCounter = 0;
//   Serial.println(analogRead(A5));
void vu3()
{
    int sensorValue;
    counterss = 0;
    static uint16_t j = 0;
    for (int i = 0; i < 100; i++)
    {
        sensorValue = analogRead(A0);
        if (sensorValue > 100)
            counterss++;
    }

    if (map(counterss, 10, 85, 80, 80) > outputValue)
        outputValue = map(counterss, 00, 40, 0, 40);
    else if (loopCounter % 2 == 0)
        outputValue -= 1;

    if (outputValue < 0)
        outputValue = 0;
    if (outputValue > 85)
        outputValue = 85;

    if (loopCounter % 100 == 0)
        randNumber = random(255);
    loopCounter++;

    for (int i = 0; i < 85; i++)
    {

        SetMyLED(i, pixels.Color(0, 0, 0, 255));
        SetLeftStripe(i, pixels.Color(0, 0, 0, 255));
    }

    if (rememberOutputValue != outputValue)
    {
        for (int i = 0; i < outputValue; i++)
        {
            SetMyLED(i, Wheel(((i * 256 / 85) + j) & 255, 1));
            SetLeftStripe(i, Wheel(((i * 256 / 85)) & 255, 1));
        }

        showAllStrips();
    }
    j++;
    if (j >= 256 * 5)
        j = 0;
    rememberOutputValue = outputValue;
}
int oldAmount = 0;
void fill()
{
    AllOff();
    int amount = map(patternInterval, 0, 255, 0, halfofPixels);
    for (int i = 0; i < amount; i++)
    {
        SetLeftStripe(i, COLORS);
        SetRightStripe(i, COLORS);
        SetLeftStripe(i + 1, 0);
        SetRightStripe(i + 1, 0);
    }
    showAllStrips();
}

void fillCenter()
{

    int col = map(patternInterval, 0, 255, 0, halfofPixels / 2);
    AllOff();
    for (int i = 0; i < col + 1; i++)
    {
        SetLeftCenterDouble(i, COLORS);
        SetRightCenterDouble(i, COLORS);
        SetRightCenterDouble(i + 1, 0);
        SetLeftCenterDouble(i + 1, 0);
    }
    showAllStrips();
}
void Balls()
{

    for (int i = 0; i < NUM_BALLS; i++)
    {
        tCycle[i] = millis() - tLast[i]; // Calculate the time since the last time the ball was on the ground

        // A little kinematics equation calculates positon as a function of time, acceleration (gravity) and intial velocity
        h[i] = 0.5 * GRAVITY * pow(tCycle[i] / 1000, 2.0) + vImpact[i] * tCycle[i] / 1000;

        if (h[i] < 0)
        {
            h[i] = 0;                         // If the ball crossed the threshold of the "ground," put it back on the ground
            vImpact[i] = COR[i] * vImpact[i]; // and recalculate its new upward velocity as it's old velocity * COR
            tLast[i] = millis();

            if (vImpact[i] < 0.01)
                vImpact[i] = vImpact0; // If the ball is barely moving, "pop" it back up at vImpact0
        }
        pos[i] = round(h[i] * (allPixelsAmount - 1) / h0); // Map "h" to a "pos" integer index position on the LED strip
    }
    if (patternInterval < 100)
    {
        // Choose color of LEDs, then the "pos" LED on
        for (int i = 0; i < NUM_BALLS; i++)
            SetMyLED(pos[i], colors[i]);
        showAllStrips();
        // FastLED.show();
        //  Then off for the next loop around
        for (int i = 0; i < NUM_BALLS; i++)
        {
            SetMyLED(pos[i], 0, 0, 0);
        }
    }
    else if (patternInterval < 150 && patternInterval > 100)
    {
        // Choose color of LEDs, then the "pos" LED on
        for (int i = 0; i < NUM_BALLS; i++)
        {
            SetLeftStripe(pos[i] / 2, colors[i]);
            SetRightStripe(pos[i] / 2, colors[i]);
        }
        showAllStrips();
        // FastLED.show();
        //  Then off for the next loop around
        for (int i = 0; i < NUM_BALLS; i++)
        {
            SetLeftStripe(pos[i] / 2, black);
            SetRightStripe(pos[i] / 2, black);
        }
    }
    else
    {

        for (int i = 0; i < NUM_BALLS; i++)
        {
            AllStripSame(pos[i] / 2, colors[i]);
        }
        showAllStrips();
        // FastLED.show();
        //  Then off for the next loop around
        for (int i = 0; i < NUM_BALLS; i++)
        {
            AllStripSame(pos[i] / 2, black);
        }
    }
}
int maxi = 0;
int led = 0;
boolean last = true;
void vutest()
{
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        if (last)
        {
            int level = analogRead(A0);
            if (level > maxi)
                maxi = level;
            int col = map(level, 0, maxi, 0, 7);
            led = map(level, 0, maxi, 0, allPixelsAmount);
            SetLeftStripe(led / 2, colors[col]);
            SetRightStripe(led / 2, colors[col]);
            // pixels.setBrightness(brightness);
            showAllStrips();
            last = false;
        }
        else
        {

            SetLeftStripe(led / 2, black);
            SetRightStripe(led / 2, black);
            // pixels.setBrightness(brightness);
            showAllStrips();
            last = true;
        }
        previousMillis = currentMillis;
    }
}
