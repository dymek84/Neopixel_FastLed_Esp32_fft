#pragma once

#include "Imports.h"
/********************** FFT ***************************/
#define SAMPLES 512         // Must be a power of 2 (512)
#define MULTIPLY_BY 1       // in case we want to amlify output
#define SAMPLING_FREQ 36000 // Hz, must be 40000 or less due to ADC conversion time. Determines
                            // maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
uint16_t AMPLITUDE = 3000;  // Depending on your audio source level, you may need to alter this
                            // value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN 35     // Signal in on this pin
#define COLOR_ORDER GRB     // If colours look wrong, play with this
#define CHIPSET WS2812B     // LED strip type

#define NUM_BANDS 32                               // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE 200                                  // Used as a crude noise filter, values below this are ignore
#define MATRIX_WIDTH 32                            // width of each matrix xres
#define MATRIX_HEIGHT 8                            // height of each matrix yres
#define BAR_WIDTH (MATRIX_WIDTH / (NUM_BANDS - 1)) // If width >= 8 light 1 LED width per bar, >= 16 light 2 LEDs width bar etc
#define TOP (MATRIX_HEIGHT - 0)                    // Don't allow the bars to go offscreen
#define SERPENTINE false                           // Set to false if your LEDS are connected end to end, true if serpentine

/*************************** MACROS ***************************/

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

/*                     matrix - stripe                     */

#define LED_PIN_STRIPE 15 // Data pin to stripe
#define NUM_LEDS_MATRIX (MATRIX_WIDTH * MATRIX_HEIGHT)
#define NUM_LEDS_STRIPE 1200
#define LED_PIN_MATRIX 23 // Data pin to matrix
#define BRIGHTNESS 125    // LED information
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define LED_VOLTS 5         // Usually 5 or 12
#define MAX_MILLIAMPS 35000 // Careful with the amount of power here if running off USB port

/********************** BOUNCING BALLS ***************************/

#define GRAVITY -9.81 // Downward (negative) acceleration of gravity in m/s^2
#define h0 2          // Starting height, in meters, of the ball (strip length)
#define NUM_BALLS 4   // Number of bouncing balls you want (recommend < 7, but 20 is fun in its own way)
#define SPEED .20     // Amount to increment RGB color by each cycle

//=======================MENU=============================
unsigned long startTime = 0;
unsigned long timeOut = 500;
boolean showMenu = false; // goes true if button is pressed
boolean moreTime = false; // goes true if button is pressed and menu is still shown
int menuNumber = 0;       // menuname
int percentage = 0;       //???
int changeColor = 0;      // COLORS value from 0 to 20 to change color from array colors[]
int changeLedBright = 0;  // stripeBrightness
int bright = map(changeLedBright, 0, 20, 0, 255);
int chageClockBright = 0;  // clockBright
int chngePatternSpeed = 0; // patternInterval
int selected = 12;         // number of pattern are now showing
int counter = 12;          // number of patter to be selected

long patternInterval = 20000;
long previousMillis = 0;
int gCurrentPatternNumber = 2;
//== END ================MENU===================== END ==

const int BRIGHTNESS_SETTINGS[3] = {5, 5, 5}; // 3 Integer array for 3 brightness settings (based on pressing+holding BTN_PIN)
int pass = 0;

//=======================LED STRIPS=============================
int firstCornerPixelNumber = 0;
int secondCornerPixelNumber = 255;
int thirdCornerPixelNumber = 512;
int fourthCornerPixelNumber = 767;

int AllLEDSAmount = NUM_LEDS_STRIPE;
int halfofPixels = NUM_LEDS_STRIPE / 2;
uint8_t gHue = 0;

uint16_t pixelCurrent = 0;
//=======================LED STRIPS=============================

//======================= RTC =============================
// DS1307ESP rtc;
//======================= RTC =============================

//=======================BOUNCING BALLS=============================

float h[NUM_BALLS];                       // An array of heights
float vImpact0 = sqrt(-2 * GRAVITY * h0); // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
float vImpact[NUM_BALLS];                 // As time goes on the impact velocity will change, so make an array to store those values
float tCycle[NUM_BALLS];                  // The time since the last time the ball struck the ground
int pos[NUM_BALLS];                       // The integer position of the dot on the strip (LED index)
long tLast[NUM_BALLS];                    // The clock time of the last ground strike
float COR[NUM_BALLS];                     // Coefficient of Restitution (bounce damping)
//=======================BOUNCING BALLS=============================

//======================= BUTTONS OPTIONS =============================
int buttonsValues[11][2] = {{86, 95}, {126, 134}, {194, 205}, {162, 173}, {332, 342}, {507, 512}, {678, 684}, {842, 856}, {927, 934}, {998, 1006}, {1018, 1023}};
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

//======================= BUTTONS OPTIONS =============================
uint8_t electric_pumpkinaaaaaa;
String currentPatternName = "None";

long delayss = 0;
long delayEEPROM = 0;

unsigned int sampling_period_us;
byte peak[MATRIX_WIDTH]; // The length of these arrays must be >= NUM_BANDS
int oldBarHeights[MATRIX_WIDTH];
int bandValues[MATRIX_WIDTH];
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime;

// Button stuff
int buttonPushCounter = 0;
bool autoChangePatterns = false;

int barMode = 0;

uint8_t mode = 0;
uint8_t strobeStatus = 0;
uint16_t strobeRate = 50;

uint8_t colorTimer = 0;
int Intensity[32] = {}; // initialize Frequency Intensity to zero
int Displacement = 1;
uint8_t userColor = 0;