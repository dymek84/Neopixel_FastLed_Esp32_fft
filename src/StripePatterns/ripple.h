

#pragma once

#include "Imports.h"

uint8_t max_bright = 128; // Overall brightness definition. It can be changed on the fly.
// Initialize our LED array. We'll be using less in operation.

struct ripple
{ // Reko Meriö's structures

    // Local definitions

    // Persistent local variables

    // Temporary local variables
    uint8_t brightness; // 0 to 255
    int8_t color;       // 0 to 255
    int16_t pos;        // -1 to NUM_LEDS  (up to 127 LED's)
    int8_t velocity;    // 1 or -1
    uint8_t life;       // 0 to 20
    uint8_t maxLife;    // 10. If it's too long, it just goes on and on. . .
    uint8_t fade;       // 192
    bool exist;         // 0 to 1

    void Move()
    {

        pos += velocity;
        life++;

        if (pos > NUM_LEDS_STRIPE - 1)
        { // Bounce back from far end.
            velocity *= -1;
            pos = NUM_LEDS_STRIPE - 1;
        }

        if (pos < 0)
        { // Bounce back from 0.
            velocity *= -1;
            pos = 0;
        }

        brightness = scale8(brightness, fade); // Adjust brightness accordingly to strip length

        if (life > maxLife)
            exist = false; // Kill it once it's expired.

    } // Move()

    void Init(uint8_t Fade, uint8_t MaxLife)
    { // Typically 216, 20

        pos = random16(NUM_LEDS_STRIPE / 20, NUM_LEDS_STRIPE - NUM_LEDS_STRIPE / 20); // Avoid spawning too close to edge.
        velocity = 1;                                                                 // -1 or 1
        life = 0;                                                                     // 0 to Maxlife
        maxLife = MaxLife;                                                            // 10 called
        exist = true;                                                                 // 0, 1
        brightness = 255;                                                             // 0 to 255
        color = millis();                                                             // hue;
        fade = Fade;                                                                  // 192 called

    } // Init()

}; // struct ripple

typedef struct ripple Ripple;

Ripple ripples[maxRipples];
void rippless()
{
    currentPatternName = "ripple";
    for (int i = 0; i < maxRipples; i += 2)
    { // Check to see if ripple has expired, and if so, create a new one.
        if (random8() > 224 && !ripples[i].exist)
        {                                  // Randomly create a new ripple if this one has expired.
            ripples[i].Init(232, 20);      // Initialize the ripple array with Fade and MaxLife values.
            ripples[i + 1] = ripples[i];   // Everything except velocity is the same for the ripple's other half. Position starts out the same for both halves.
            ripples[i + 1].velocity *= -1; // We want the other half of the ripple to go opposite direction.
        }
    }
    for (uint16_t l = 0; l < NUM_LEDS_STRIPE; l++)
    {
        stripe[l] = ColorFromPalette(currentPalette, colorTimer + l, 255, LINEARBLEND);
    }
    for (int i = 0; i < maxRipples; i++)
    { // Move the ripple if it exists
        if (ripples[i].exist)
        {
            stripe[ripples[i].pos] = ColorFromPalette(currentPalette, ripples[i].color, ripples[i].brightness, LINEARBLEND);
            ripples[i].Move();
        }
    }

    fadeToBlackBy(stripe, NUM_LEDS_STRIPE, 160);

} // rippless()
