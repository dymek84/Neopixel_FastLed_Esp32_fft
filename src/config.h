#pragma once

#include "Imports.h"

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

const int BRIGHTNESS_SETTINGS[3] = {5, 5, 5}; // 3 Integer array for 3 brightness settings (based on pressing+holding BTN_PIN)
int x2 = matrix2.width();
int pass = 0;

//=======================LED STRIPS=============================
int firstCornerPixelNumber = 0;
int secondCornerPixelNumber = 255;
int thirdCornerPixelNumber = 512;
int fourthCornerPixelNumber = 767;

int AllLEDSAmount = LED_STRIP_PIXELS_AMOUNT;
int halfofPixels = LED_STRIP_PIXELS_AMOUNT / 2;
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

//======================= BUTTONS OPTIONS =============================
uint8_t electric_pumpkinaaaaaa;
String currentPatternName = "None";

long delayss = 0;
long delayEEPROM = 0;
