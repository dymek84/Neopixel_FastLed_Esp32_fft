
#include <Arduino.h>
#include "D_include.h"
#define SERIAL_BAUD_RATE 115200 // Serial baud rate used for debugging and the virtual matrix
#define DEBUG(STR) Serial.print(STR);
#define DEBUGLN(STR) Serial.println(STR);
#define DEBUGF(STR, ...) Serial.printf(STR, __VA_ARGS__);

Visualization visualization;
CRGB matrix_Array[22];
CRGB stripe_Array[22];

void loadNextAnimation()
{
    visualization.nextVis();
}

void loadPrevAnimation()
{
    visualization.prevVis();
}
void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    delay(1000);
    DEBUGLN("\n\nLED Matrix Controller. Developed by Dymek.\n")
}

void loop()
{
    visualization.update(matrix_Array);
}