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
#define LED_STRIP_PIXELS_AMOUNT 1200
#define LED_PIN_STRIPE 15 // Data pin to stripe
#define NUM_LED_MATRIX (MATRIX_WIDTH * MATRIX_HEIGHT)
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
