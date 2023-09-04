#pragma once
#define FASTLED_INTERNAL
#define FASTLED_ALL_PINS_HARDWARE_SPI
#include "Imports.h"

/********************** FFT ***************************/
#define SAMPLES 256         // Must be a power of 2 (512)
#define MULTIPLY_BY 1       // in case we want to amlify output
#define SAMPLING_FREQ 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines
                            // maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
uint16_t AMPLITUDE = 1000;  // Depending on your audio source level, you may need to alter this
                            // value. Can be used as a 'sensitivity' control.
#define FREQUENCY_BANDS 14  // band number
#define COLOR_ORDER GRB     // If colours look wrong, play with this
#define CHIPSET WS2812B     // LED strip type
#define NUM_BANDS 8         // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE 500           // Used as a crude noise filter, values below this are ignore
#define MATRIX_WIDTH 32     // width of each matrix [xres]-[NUM_COLS]
#define MATRIX_HEIGHT 8     // height of each matrix [yres]-[NUM_ROWS]
#define kMatrixWidth MATRIX_WIDTH
#define kMatrixHeight MATRIX_HEIGHT
#define M_WIDTH MATRIX_WIDTH
#define M_HEIGHT MATRIX_HEIGHT
#define NUM_COLS 32
#define NUM_ROWS 8
#define LED_COLS NUM_COLS
#define LED_ROWS NUM_ROWS
#define WIDTH (LED_COLS)
#define HEIGHT (LED_ROWS)
#define BAR_WIDTH (MATRIX_WIDTH / (NUM_BANDS - 1)) // If width >= 8 light 1 LED width per bar, >= 16 light 2 LEDs width bar etc
#define TOP (MATRIX_HEIGHT - 0)                    // Don't allow the bars to go offscreen
#define SERPENTINE false                           // Set to false if your LEDS are connected end to end, true if serpentine
const uint8_t sampleWindow = 50;                   // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
// int Intensity[32] = {}; // initialize Frequency Intensity to zero
uint8_t Displacement = 1;
unsigned int sampling_period_us;
byte peakMatrix[MATRIX_WIDTH]; // The length of these arrays must be >= NUM_BANDS
byte peakStripe[MATRIX_WIDTH]; // The length of these arrays must be >= NUM_BANDS
uint8_t oldBarHeights[MATRIX_WIDTH];
uint8_t bandValues[MATRIX_WIDTH];
int spectrumByte[MATRIX_WIDTH];
uint8_t stripeValues[MATRIX_WIDTH];
uint8_t matrixValues[MATRIX_WIDTH];
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTimeForAudio;
float reference = log10(100.0);
int squelch = 1; // Squelch, cuts out low level sounds
int gain = 50;
uint16_t micData;

double FFT_MajorPeak = 0;
double FFT_Magnitude = 0;
double fftBin[SAMPLES];
double fftCalc[8];
int patternStripe, patternMatrix, micSquelch, micSensytivity, matrixSpeed, stripeSpeed, autoPalMat, autoPalStr;
long lastUpdateMatrix, lastUpdateStripe, mappedMatrixInterval, mappedStripeInterval;

// Table of linearNoise results to be multiplied by squelch in order to reduce squelch across fftResult bins.
int linearNoise[8] = {34, 26, 20, 9, 4, 3, 2, 2};

// Table of multiplication factors so that we can even out the frequency response.
double fftResultPink[8] = {1.30, 1.23, 1.58, 1.75, 1.99, 1.90, 2.77, 3.53};
/********************** FFT ***************************/
//
//
/********************** matrix - stripe  ***************************/
#define BRIGHTNESS 150
#define MATRIX_DATA_PIN 14
#define NUM_LEDS_MATRIX 256
#define CENTER_LED_MATRIX NUM_LEDS_MATRIX / 2
#define STRIPE_DATA_PIN 12
#define NUM_LEDS_STRIPE 66
#define CENTER_LED_STRIPE NUM_LEDS_STRIPE / 2
int centerLedStripe = NUM_LEDS_STRIPE / 2;
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define LED_VOLTS 5         // Usually 5 or 12
#define MAX_MILLIAMPS 35000 // Careful with the amount of power here if running off USB port
/********************** matrix - stripe  ***************************/
//
//
/********************** OUTPUT/INPUT PINS ***************************/
// #define buttons 34
// #define photoresistor 39

#define AUDIO_IN_PIN 38 // Signal in on this pin
#define MIC_IN_PIN 35   // Signal in on this pin
/********************** BOUNCING BALLS ***************************/
//
//
/********************** RIPPLE ***************************/
#define GRAVITY -9.81  // Downward (negative) acceleration of gravity in m/s^2
#define h0 2           // Starting height, in meters, of the ball (strip length)
#define NUM_BALLS 4    // Number of bouncing balls you want (recommend < 7, but 20 is fun in its own way)
#define SPEED .20      // Amount to increment RGB color by each cycle
#define maxRipples 100 // Min is 2 and value has to be divisible by two because each ripple has a left and right component. This cuts down on bouncing code.
/********************** RIPPLE ***************************/
//
//
/********************** MENU ***************************/
unsigned long startTime = 0;
unsigned long timeOut = 500;
boolean showMenu = false;  // goes true if button is pressed
boolean moreTime = false;  // goes true if button is pressed and menu is still shown
uint8_t menuNumber = 0,    // menuname
    percentage = 0,        //???
    changeColor = 0,       // COLORS value from 0 to 20 to change color from array colors[]
    changeLedBright = 0,   // stripeBrightness
    chageClockBright = 0,  // clockBright
    chngePatternSpeed = 0, // patternInterval
    selected = 12,         // number of pattern are now showing
    counter = 12;          // number of patter to be selected
uint8_t bright = map(changeLedBright, 0, 20, 0, 255);
long patternInterval = 20;
long previousMillis = 0;
int gCurrentPatternNumber = 1;
String welcommessage;
/**********************MENU===================== END ==
//
//
/**********************LED STRIPS***************************/
int firstCornerPixelNumber = 0;
int secondCornerPixelNumber = 255;
int thirdCornerPixelNumber = 512;
int fourthCornerPixelNumber = 767;

int AllLEDSAmount = NUM_LEDS_STRIPE;
int halfofPixels = NUM_LEDS_STRIPE / 2;

/********************** LED STRIPS***************************/
//
//
/********************** RTC ***************************/
// DS1307ESP rtc;
/********************** RTC ***************************/
//
//
/********************** BOUNCING BALLS ***************************/
float h[NUM_BALLS];                       // An array of heights
float vImpact0 = sqrt(-2 * GRAVITY * h0); // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
float vImpact[NUM_BALLS];                 // As time goes on the impact velocity will change, so make an array to store those values
float tCycle[NUM_BALLS];                  // The time since the last time the ball struck the ground
int pos[NUM_BALLS];                       // The integer position of the dot on the strip (LED index)
long tLast[NUM_BALLS];                    // The clock time of the last ground strike
float COR[NUM_BALLS];                     // Coefficient of Restitution (bounce damping)
/********************** BOUNCING BALLS ***************************/
//
//
/********************** BUTTONS OPTIONS ***************************/
uint8_t buttonDebounceTime = 200;
uint16_t delayss;
int buttonsValues[11][2] = {
    {92, 150},
    {210, 134},
    {194, 205},
    {162, 173},
    {332, 342},
    {507, 512},
    {678, 684},
    {842, 856},
    {927, 934},
    {998, 1006},
    {1018, 1023}};
String buttonNames[11] = {
    "Select",
    "Pattern Minus",
    "Pattern Plus",
    "Led Brighness Minus",
    "Led Brighness Plus",
    "Color Minus",
    "Color Plus",
    "Speed Minus",
    "Speed Plus",
    "Clock Brighness Minus",
    "Clock Brighness Plus",
};

/********************** BUTTONS OPTIONS ***************************/

CRGBPalette16 currentPaletteStripe;
CRGBPalette16 targetPaletteStripe;

CRGBPalette16 currentPaletteMatrix;
CRGBPalette16 targetPaletteMatrix;

CRGB clockColor;
typedef enum
{
    MATRIXLEDS = 1,
    STRIPELEDS = 0
} ledTypeConnected;
struct ModeType
{
    uint8_t Brightness = 255U; // not used here
    uint8_t Speed = 250;       // 1-255 is speed
    uint8_t Scale = 70;        // 1-100 is something parameter
};
byte custom_eff = 1;
byte FPSdelay;
#define LOW_DELAY 0

#define NUM_LAYERSMAX 2

bool loadingFlag = true;
ModeType modes[1];

uint8_t
    noise3d[NUM_LAYERSMAX][WIDTH][HEIGHT],
    currentMode = 0,
    selectedSettings = 1,
    deltaValue,
    pcnt,
    step,
    deltaHue,
    deltaHue2,
    hue,
    hue2,
    paletteDuration = 10,
    colorHue = 0,
    delayStripe = 0,
    BeatsPerMinute = 60,
    colorHueMatrix,
    colorHueStripe,
    CurrentStripePatternNumber = 0,
    CurrentMatrixPatternNumber = 0,
    currentPaletteStripeIndex = 0,
    currentPaletteMatrixIndex = 0;
String
    welcomeMessage,
    scrolltext,
    ssidAP = "Esp-LedServerAccessPoint",
    passwordAP,
    ssid,
    pass;
int
    paletteTime,
    scrollspeed,
    matrixBrightness,
    stripBrightness,
    pixelCurrent,
    year,
    month,
    day,
    hour, minute,
    second;
bool
    isAudioStripe,
    isAudioMatrix,
    clockOnOff,
    messageIsShown = false,
    showMessage;
uint16_t
    patternStripeInterval = 0,
    patternMatrixInterval = 0;
/********************** PATTERNS / PALETTES ***************************/
struct NamedPalette
{
    const TProgmemRGBGradientPalettePtr Palette;
    const String Name;

    NamedPalette(TProgmemRGBGradientPalettePtr p, const String n)
        : Palette(p), Name(n) {}
};

// extern NamedPalette Palette_List[];
extern const uint16_t NUMpalettes;

/********************** PATTERNS / PALETTES ***************************/
//
//
/*************************** MACROS ***************************/
#define qsubd(x, b) ((x > b) ? b : 0)                            // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b) ((x > b) ? x - b : 0)                        // Analog Unsigned subtraction macro. if result <0, then => 0
#define FOR_i(from, to) for (int i = (from); i < (to); i++)      // loop for "i" to ascending
#define FOR_j(from, to) for (int j = (from); j < (to); j++)      // loop for "j" to ascending
#define FOR_i_down(from, to) for (int i = (from); i > (to); i--) // loop for "i" to descending
#define FOR_j_down(from, to) for (int j = (from); j > (to); j--) // loop for "j" to descending
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#define Minim(a, b) (((a) < (b)) ? (a) : (b))
#define Maxim(a, b) (((a) > (b)) ? (a) : (b))
#define PALETTE_NAME(x) NamedPalette(x, #x)
/*************************** MACROS ***************************/

#define HTTP_PORT 80
int result_vu[8],
    input_vu[8];

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int dayLightOffset_sec = 3600;

// background color
uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;
int myhue = 0;
int color;
int center = 0;
int steper = -1;
int maxSteps = 16;
float fadeRate = 0.80;

int thishues = 95;
int thissats = 255;
int thisdirs = 0;
bool huerots = 0;
int thisdelays = 50;