

#pragma once

#include "Imports.h"

void nextPatternStripe();
void prevPatternStripe();
void nextPatternMatrix();
void prevPatternMatrix();

void nextPaletteStripe(bool isAuto);
void prevPaletteStripe();
void nextPaletteMatrix(bool isAuto);
void prevPaletteMatrix();

void setBrightMatrix(uint8_t bright);
void setBrightStripe(uint8_t bright);
void setSpeedMatrix(uint16_t speed);
void setSpeedStripe(uint16_t speed);

void minimumDelayFromPatternsMatrix(uint16_t delay);
void minimumDelayFromPatternsStripe(uint16_t delay);