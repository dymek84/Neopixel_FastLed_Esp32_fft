#ifndef _DEF_CON_OBJ_INO__
#define _DEF_CON_OBJ_INO__

#include "Imports.h"

#define SAMPLES 512 // Must be a power of 2 (64)
#define MULTIPLY_BY 1
#define xres 32 // Total number of  columns in the display
#define yres 8  // Total number of  rows in the display
#define audio 35

double vReal[SAMPLES];
double vImag[SAMPLES];
int Intensity[6] = {}; // initialize Frequency Intensity to zero
int Displacement = 1;
arduinoFFT FFT = arduinoFFT(); // Create FFT object
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
//=======================MENU=============================

#define LED_PIN 15 // Data pin to Long Led Light
#define NUM_LEDS_MATRIX (xres * yres)

#define BRIGHTNESS 125 // LED information
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BUTTON_PIN 3

//=======================FASTLED_MATRIX=============================
CRGB matrix[NUM_LEDS_MATRIX]; // Create LED Object

//=======================AUDIO IN=============================

//=======================AUDIO IN =============================

//=======================FFT=============================

//=======================FFT=============================

#define FASTLED_ESP32_SPI_BUS HSPI
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
int gCurrentPatternNumber = 2;
//== END ================MENU===================== END ==

Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(32, 8, LED_PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);
int x2 = matrix2.width();
int pass = 0;

CRGB blue(0, 0, 255);
CRGB deep_blue_gatoraide(0, 32, 255);
CRGB blue_gatoraide(0, 127, 255);
CRGB cyan(0, 255, 255);
CRGB aqua(0, 255, 127);
CRGB electric_mint(0, 255, 32);
CRGB green(0, 255, 0);
CRGB electric_lime(32, 255, 0);
CRGB green_yellow(127, 255, 0);
CRGB yellow(255, 255, 0);
CRGB orange(255, 127, 0);
CRGB electric_pumpkin(255, 32, 0);
CRGB red(255, 0, 0);
CRGB deep_pink(255, 0, 32);
CRGB pink(255, 0, 127);
CRGB magenta(255, 0, 255);
CRGB purple(127, 0, 255);
CRGB deep_purple(32, 0, 255);
CRGB white(255, 255, 255);
CRGB orange2(230, 80, 0);
CRGB black(0, 0, 0);
CRGB arrayofcolors[]{blue, deep_blue_gatoraide, blue_gatoraide, cyan, aqua, electric_mint, orange2, deep_purple, purple, magenta, pink, deep_pink, red, electric_pumpkin, orange, yellow, green_yellow, electric_lime, green};

//=======================LED STRIPS=============================
int firstCornerPixelNumber = 0;
int secondCornerPixelNumber = 255;
int thirdCornerPixelNumber = 512;
int fourthCornerPixelNumber = 767;

#define LED_STRIP_PIXELS_AMOUNT 555
int AllLEDSAmount = LED_STRIP_PIXELS_AMOUNT;
int halfofPixels = LED_STRIP_PIXELS_AMOUNT / 2;
uint8_t gHue = 0;
CRGB strip1[LED_STRIP_PIXELS_AMOUNT]; // Create LED Object

#define strip1_PIN 17 // Blue[1]
uint16_t pixelCurrent = 0;
//=======================LED STRIPS=============================

//======================= RTC =============================
// DS1307ESP rtc;
//======================= RTC =============================

//=======================BOUNCING BALLS=============================
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
//=======================BOUNCING BALLS=============================

//======================= BUTTONS OPTIONS =============================
int buttonsValues[11][2] = {{86, 95}, {126, 134}, {194, 205}, {162, 173}, {332, 342}, {507, 512}, {678, 684}, {842, 856}, {927, 934}, {998, 1006}, {1018, 1023}};
char *buttonNames[11] = {
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
#define NUM_LEDS 180
long delayss = 0;
//======================= BUTTONS OPTIONS =============================
uint8_t electric_pumpkinaaaaaa;
String currentPatternName = "None";

#endif