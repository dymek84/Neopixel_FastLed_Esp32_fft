

#pragma once
#include "Imports.h"

// Colors mode 1 These are the colors from the TRIBAR when using Ledstrip
#define TriBar_Color_Top 0, 255, 255     // Red CHSV
#define TriBar_Color_Bottom 95, 255, 255 // Green CHSV
#define TriBar_Color_Middle 45, 255, 255 // Yellow CHSV

#define TriBar_Color_Top_Peak 0, 255, 255     // Red CHSV
#define TriBar_Color_Bottom_Peak 95, 255, 255 // Green CHSV
#define TriBar_Color_Middle_Peak 45, 255, 255 // Yellow CHSV

// Colors mode 1 These are the colors from the TRIBAR when using HUB75
#define TriBar_RGB_Top 255, 0, 0      // Red CRGB
#define TriBar_RGB_Bottom 0, 255, 0   // Green CRGB
#define TriBar_RGB_Middle 255, 255, 0 // Yellow CRGB

#define TriBar_RGB_Top_Peak 255, 0, 0      // Red CRGB
#define TriBar_RGB_Bottom_Peak 0, 255, 0   // Green CRGB
#define TriBar_RGB_Middle_Peak 255, 255, 0 // Yellow CRGB
int CalibrationType = 0;                   // 0=none, 1=White, 2=Pink

// Colors mode 2
#define RainbowBar_Color (x / BAR_WIDTH) * (255 / numBands), 255, 255
#define PeakColor1 0, 0, 255 // white CHSV

// Colors mode 3
#define PeakColor2 0, 0, 255 // white CHSV

CRGBPalette16 purplePal = purple_gp;

// Colors mode 4
#define SameBar_Color1 0, 255, 255 // red  CHSV
#define PeakColor3 160, 255, 255   // blue CHSV

// Colors mode 5
#define SameBar_Color2 160, 255, 255 // blue  CHSV
#define PeakColor4 0, 255, 255       // red CHSV

// Colors mode 6

CRGBPalette16 heatPal = redyellow_gp;
// no peaks

// no peaks

// Colors mode 8
DEFINE_GRADIENT_PALETTE(mark_gp22){
    0,
    255,
    218,
    0, // Yellow
    64,
    200,
    200,
    200, // white
    128,
    141,
    0,
    100, // pur
    192,
    200,
    200,
    200, // white
    255,
    255,
    218,
    0,
}; // Yellow
CRGBPalette16 markPal2 = redyellow_gp;

// Colors mode 9
// no bars only peaks
DEFINE_GRADIENT_PALETTE(mark_gp233){
    0,
    231,
    0,
    0, // red
    64,
    200,
    200,
    200, // white
    128,
    200,
    200,
    200, // white
    192,
    200,
    200,
    200, // white
    255,
    231,
    0,
    0,
}; // red
CRGBPalette16 markPal = redyellow_gp;

// Colors mode 10
// no bars only peaks
#define PeakColor5 160, 255, 255 // blue CHSV

// These are the colors from the TRIPEAK mode 11
// no bars
#define TriBar_Color_Top_Peak2 0, 255, 255     // Red CHSV
#define TriBar_Color_Bottom_Peak2 95, 255, 255 // Green CHSV
#define TriBar_Color_Middle_Peak2 45, 255, 255 // Yellow CHSV

#define ChangingBar_Color y * (255 / kMatrixHeight) + colorHueMatrix, 255, 255
//************ Mode 0 ***********
void changingBarsLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                FastLedMatrix->drawPixel(x, y, CHSV(ChangingBar_Color));
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}

//************ Mode 1 ***********
void TriBarLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                if (y < (kMatrixHeight / 3))
                    FastLedMatrix->drawPixel(x, y, CHSV(TriBar_Color_Top)); // Top red
                else if (y > (1 * kMatrixHeight / 2))
                    FastLedMatrix->drawPixel(x, y, CHSV(TriBar_Color_Bottom)); // green
                else
                    FastLedMatrix->drawPixel(x, y, CHSV(TriBar_Color_Middle)); // yellow
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}

void TriPeakLS(int band)
{
    int xStart = BAR_WIDTH * band;
    int peakHeight = TOP - peakMatrix[band] - 1;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        if (peakHeight < 4)
            FastLedMatrix->drawPixel(x, peakHeight, CHSV(TriBar_Color_Top_Peak)); // Top red
        else if (peakHeight > 8)
            FastLedMatrix->drawPixel(x, peakHeight, CHSV(TriBar_Color_Bottom_Peak)); // green
        else
            FastLedMatrix->drawPixel(x, peakHeight, CHSV(TriBar_Color_Middle_Peak)); // yellow
    }
}
//************ Mode 2 ***********
void rainbowBarsLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                FastLedMatrix->drawPixel(x, y, CHSV(RainbowBar_Color));
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}

void NormalPeakLS(int band, int H, int S, int V)
{
    int xStart = BAR_WIDTH * band;
    int peakHeight = TOP - peakMatrix[band] - 1;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        FastLedMatrix->drawPixel(x, peakHeight, CHSV(H, S, V));
    }
}

//************ Mode 3 ***********

void purpleBarsLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                FastLedMatrix->drawPixel(x, y, ColorFromPalette(purplePal, y * (255 / (barHeight + 1))));
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}

// for peaks see mode 2

//************ Mode 4 ***********

void SameBarLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                FastLedMatrix->drawPixel(x, y, CHSV(SameBar_Color1)); // blue
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}
// for peaks see mode 2

//************ Mode 5 ***********
void SameBar2LS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                FastLedMatrix->drawPixel(x, y, CHSV(SameBar_Color2)); // blue
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}
// for peaks see mode 2

//************ Mode 6 ***********
void centerBarsLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    int center = TOP / 2;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        if (barHeight % 2 == 0)
            barHeight--;
        if (barHeight < 0)
            barHeight = 1; // at least a white line in the middle is what we want
        int yStart = ((kMatrixHeight - barHeight) / 2);
        for (int y = yStart; y <= (yStart + barHeight); y++)
        {
            int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
            FastLedMatrix->drawPixel(x, y, ColorFromPalette(heatPal, colorIndex));
        }
        for (int y = barHeight / 2; y < TOP; y++)
        {
            FastLedMatrix->drawPixel(x, center + y + 1, CRGB(0, 0, 0)); // make unused pixel bottom black
            FastLedMatrix->drawPixel(x, center - y - 2, CRGB(0, 0, 0)); // make unused pixel bottom black
        }
    }
}

//************ Mode 7 ***********
void centerBars2LS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    int center = TOP / 2;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        if (barHeight % 2 == 0)
            barHeight--;
        if (barHeight < 0)
            barHeight = 1; // at least a white line in the middle is what we want
        int yStart = ((kMatrixHeight - barHeight) / 2);
        for (int y = yStart; y <= (yStart + barHeight); y++)
        {
            int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
            FastLedMatrix->drawPixel(x, y, ColorFromPalette(markPal, colorIndex));
        }
        for (int y = barHeight / 2; y < TOP; y++)
        {
            FastLedMatrix->drawPixel(x, center + y + 1, CRGB(0, 0, 0)); // make unused pixel bottom black
            FastLedMatrix->drawPixel(x, center - y - 2, CRGB(0, 0, 0)); // make unused pixel bottom black
        }
    }
}

//************ Mode 8 ***********
void centerBars3LS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    int center = TOP / 2;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        if (barHeight % 2 == 0)
            barHeight--;
        if (barHeight < 0)
            barHeight = 1; // at least a white line in the middle is what we want
        int yStart = ((kMatrixHeight - barHeight) / 2);
        for (int y = yStart; y <= (yStart + barHeight); y++)
        {
            int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
            FastLedMatrix->drawPixel(x, y, ColorFromPalette(markPal2, colorIndex));
        }
        for (int y = barHeight / 2; y < TOP; y++)
        {
            FastLedMatrix->drawPixel(x, center + y + 1, CRGB(0, 0, 0)); // make unused pixel bottom black
            FastLedMatrix->drawPixel(x, center - y - 2, CRGB(0, 0, 0)); // make unused pixel bottom black
        }
    }
}
//************ Mode 9 ***********
void BlackBarLS(int band, int barHeight)
{
    int xStart = BAR_WIDTH * band;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        for (int y = TOP; y >= 0; y--)
        {
            if (y >= TOP - barHeight)
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
            else
            {
                FastLedMatrix->drawPixel(x, y, CRGB(0, 0, 0)); // make unused pixel in a band black
            }
        }
    }
}
CRGBPalette16 outrunPal = outrun_gp;
void outrunPeakLS(int band)
{
    int xStart = BAR_WIDTH * band;
    int peakHeight = TOP - peakMatrix[band] - 1;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        FastLedMatrix->drawPixel(x, peakHeight, ColorFromPalette(outrunPal, peakHeight * (255 / kMatrixHeight)));
    }
}

//************ Mode 10 ***********
void TriPeak2LS(int band)
{
    int xStart = BAR_WIDTH * band;
    int peakHeight = TOP - peakMatrix[band] - 1;
    for (int x = xStart; x < xStart + BAR_WIDTH; x++)
    {
        if (peakHeight < 4)
            FastLedMatrix->drawPixel(x, peakHeight, CHSV(TriBar_Color_Top_Peak2)); // Top red
        else if (peakHeight > 8)
            FastLedMatrix->drawPixel(x, peakHeight, CHSV(TriBar_Color_Bottom_Peak2)); // green
        else
            FastLedMatrix->drawPixel(x, peakHeight, CHSV(TriBar_Color_Middle_Peak2)); // yellow
    }
}
