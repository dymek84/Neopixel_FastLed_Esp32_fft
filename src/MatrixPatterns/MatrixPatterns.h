
#pragma once
#define stripethickness 33
#include "Imports.h"
#include "pgmspace.h"

CRGBPalette16 Pal = CRGBPalette16(CRGB::Black, CRGB::Red);

static uint8_t theta = 0;
int LEDposx = 0; // starting x position for the LED
int LEDposy = 0; // starting y posiiton for the LED
float timevalu = 0.0000001;
void Twirl()
{ // routine was found in https://stackoverflow.com/questions/3365171/calculating-the-angle-between-two-lines-without-having-to-calculate-the-slope
  // Serial.println("Twirl");
  timevalu = millis();
  LEDposx = 11.5 + 18 * (sin(timevalu / 1000)); // moves the centre around
  LEDposy = 4.5 + 3 * (cos(timevalu / 1000));
  theta = theta + 10;
  for (byte i = 0; i < 32; i++)
  {
    for (byte j = 0; j < LEDposy; j++)
    {
      int r = (MatrixArray[j][i]);
      int dx1 = i - LEDposx;
      int dy1 = j - LEDposy;
      float l2 = (dx1 * dx1 + dy1 * dy1);
      float angle2 = acos(dx1 / sqrt(l2)); // gives the angle of pixel (i,j) with the horizontal (1,0) in radians
      int angle3 = angle2 * 40.585;        // scale the radian value to integer 0-255 (where 255 corresponds to 2 radians = 3.1415)
      int delta = theta - angle3;          // what is the difference of the pixel's angle and the theta value
      if (delta >= 0 && delta < 127)
      {
        matrix[r] = ColorFromPalette(currentPalette, map(i, 0, 32, 255, 0), 255, LINEARBLEND);
      }
      else
      {
        matrix[r] = ColorFromPalette(currentPalette, map(i, 0, 32, 0, 255), 255, LINEARBLEND);
      }
    }
    for (byte j = LEDposy; j < 8; j++)
    {
      int r = (MatrixArray[j][i]);
      int dx1 = i - LEDposx;
      int dy1 = j - LEDposy;
      float l2 = (dx1 * dx1 + dy1 * dy1);
      float angle2 = acos(dx1 / sqrt(l2)); // gives the angle of pixel (i,j) with the horizontal (1,0) in radians
      int angle3 = angle2 * 40.585;        //
      angle3 = 256 - angle3;
      int delta = theta - angle3; // what is the difference of the pixel's angle and the theta value
      matrix[r] = ColorFromPalette(currentPalette, map(i, 0, 32, 0, 255), 255, LINEARBLEND);
      if (delta >= 0 && delta < 127)
      {
        matrix[r] = ColorFromPalette(currentPalette, map(i, 0, 32, 255, 0), 255, LINEARBLEND);
      }
      if (delta >= -255 && delta < -127)
      {
        matrix[r] = ColorFromPalette(currentPalette, map(i, 0, 32, 255, 0), 255, LINEARBLEND);
      }
    }
  }
}

void Bands()
{ // routine was found in https://stackoverflow.com/questions/3365171/calculating-the-angle-between-two-lines-without-having-to-calculate-the-slope
  // Serial.println("Bands");
  //  i and ja are the column and row numbers. These are added together, then the modulo with the stripethickness of the result is taken. This results in diagonally incrementing numbers scaled from 0 to the
  //  'stripethickness' value. These are animatied by adding a counter value, then used to colour the LEDs

  for (byte i = 0; i < 32; i++)
  {
    for (byte j = 0; j < 8; j++)
    {
      byte modulo = (i + j + colorTimer) % stripethickness;
      modulo = map(modulo, 0, stripethickness, 0, 2); // reduces the 'bit depth'
      modulo = map(modulo, 0, 1, 0, 255);             // scales it back to full

      int r = (MatrixArray[j][i]);
      matrix[r] = ColorFromPalette(currentPalette, modulo, 255, LINEARBLEND); // when modulo = 255 this gives colour 255,127,0 = orange; when it is 0, it is 0,0,255 = blue
    }
  }
}
void Enoise()
{
  static bool eff = 1;
  EVERY_N_MILLISECONDS(25000) { eff ^= 1; } // speed of  effect change

  uint32_t ms = millis();

  for (byte y = 0; y < MATRIX_HEIGHT; y++)
  {
    for (byte x = 0; x < MATRIX_WIDTH; x++)
    {
      uint16_t pixelHue = inoise16((uint32_t)x * 5000, (uint32_t)y * 5000 + ms * 10, ms * 20);
      uint8_t pixelHue8 = inoise8(x * 15, y * 15 + ms / 8, ms / 70);
      matrix[XY(x, y)] = ColorFromPalette(currentPalette, pixelHue8 + ms / 20, 255, LINEARBLEND);
    }
  }
}

void drawCircle(int x0, int y0, int radius, const CRGB &color)
{
  int a = radius, b = 0;
  int radiusError = 1 - a;

  if (radius == 0)
  {
    drawPixelXY(x0, y0, color);
    return;
  }
  while (a >= b)
  {
    drawPixelXY(a + x0, b + y0, color);
    drawPixelXY(b + x0, a + y0, color);
    drawPixelXY(-a + x0, b + y0, color);
    drawPixelXY(-b + x0, a + y0, color);
    drawPixelXY(-a + x0, -b + y0, color);
    drawPixelXY(-b + x0, -a + y0, color);
    drawPixelXY(a + x0, -b + y0, color);
    drawPixelXY(b + x0, -a + y0, color);
    b++;
    if (radiusError < 0)
      radiusError += 2 * b + 1;
    else
    {
      a--;
      radiusError += 2 * (b - a + 1);
    }
  }
}
bool loadingFlag = true;
int rad[(MATRIX_HEIGHT + MATRIX_WIDTH) / 8];
byte posx[(MATRIX_HEIGHT + MATRIX_WIDTH) / 8], posy[(MATRIX_HEIGHT + MATRIX_WIDTH) / 8];
void drop()
{
  // Serial.println("drop");

  if (loadingFlag)
  {
    loadingFlag = false;

    for (int i = 0; i < ((MATRIX_HEIGHT + MATRIX_WIDTH) / 8) - 1; i++)
    {
      posx[i] = random(MATRIX_WIDTH);
      posy[i] = random(MATRIX_HEIGHT);
      rad[i] = random(-1, (MATRIX_HEIGHT + MATRIX_WIDTH) / 2);
    }
  }
  fillAll(ColorFromPalette(currentPalette, colorTimer));

  for (uint8_t i = 0; i < ((MATRIX_HEIGHT + MATRIX_WIDTH) / 8) - 1; i++)
  {
    drawCircle(posx[i], posy[i], rad[i], ColorFromPalette(currentPalette, (256 / 16) * 8.5 - rad[i] * 5 + colorTimer));
    drawCircle(posx[i], posy[i], rad[i] - 1, ColorFromPalette(currentPalette, (256 / 16) * 7.5 - rad[i] * 5 + colorTimer));
    if (rad[i] >= (MATRIX_HEIGHT + MATRIX_WIDTH) / 2)
    {
      rad[i] = -1;
      posx[i] = random(MATRIX_WIDTH);
      posy[i] = random(MATRIX_HEIGHT);
    }
    else
      rad[i]++;
  }
}
unsigned long timer;

uint16_t _scale;
static float fmap(const float x, const float in_min, const float in_max, const float out_min, const float out_max)
{
  return (out_max - out_min) * (x - in_min) / (in_max - in_min) + out_min;
}
float adjastHeight = fmap(MATRIX_HEIGHT, 8, 32, 28, 12);
uint16_t adjScale = map(MATRIX_WIDTH, 8, 64, 310, 63);
byte scale = 80;
byte speed = 92;
void aurora()
{
  // Serial.println("aurora");
  if (loadingFlag)
  {
    loadingFlag = false;

    adjastHeight = map((float)MATRIX_HEIGHT, 8, 32, 28, 12);
    adjScale = map((int)MATRIX_WIDTH, 8, 32, 310, 127);
  }
  byte _speed = 16;
  _scale = adjScale - 55;
  for (byte x = 0; x < MATRIX_WIDTH; x++)
  {
    for (byte y = 0; y < MATRIX_HEIGHT; y++)
    {
      timer++;
      uint16_t i = x * y;
      matrix[XY(x, y)] =
          ColorFromPalette(currentPalette,
                           qsub8(
                               inoise8(i % 2 + x * _scale,
                                       y * 16 + timer % 16,
                                       timer / _speed),
                               fabs((float)MATRIX_HEIGHT * 2. - (float)y) * adjastHeight));

      // CRGB temColor = matrix[XY(x, y)];
      // matrix[XY(x, y)].g = temColor.r;
      // matrix[XY(x, y)].r = temColor.g;
      // matrix[XY(x, y)].g /= 6;
      // matrix[XY(x, y)].r += matrix[XY(x, y)].r < 206 ? 48 : 0;
      //         matrix[XY(x, y)].b += 48;
      // matrix[XY(x, y)].g += matrix[XY(x, y)].g < 206 ? 48 : 0;
    }
  }
}

void bpmMatrix()
{
  uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);

  for (int i = 0; i < NUM_LEDS_MATRIX; i++)
  {
    matrix[i] = ColorFromPalette(currentPalette, colorTimer + (i * 2), beat - colorTimer + (i * 10));
  }
}

CRGBPalette16 fire_for_fire(fire_gp);
void Fire()
{
  // Serial.println("fire");

  uint8_t speedy = 1;
  uint8_t _scale = 120;
  uint32_t a = millis();
  for (byte i = 0U; i < MATRIX_WIDTH; i++)
  {
    for (byte j = 0U; j < MATRIX_HEIGHT; j++)
    {
      drawPixelXY((MATRIX_WIDTH - 1) - i, j, ColorFromPalette(fire_for_fire, qsub8(inoise8(i * _scale, j * _scale + a, a / speedy), abs8(j - (MATRIX_HEIGHT - 1)) * 255 / (MATRIX_HEIGHT - 1)), 255));
    }
  }
}
void Wave()
{
  for (byte i = 0; i < MATRIX_WIDTH; i++)
  {
    byte thisVal = inoise8(i * 45, millis(), millis());
    byte thisMax = map(thisVal, 0, 255, 0, MATRIX_HEIGHT);
    for (byte j = 0; j < thisMax; j++)
    {
      matrix[XY(i, j)] = ColorFromPalette(currentPalette, map(j, 0, thisMax, 250, 0), 255, LINEARBLEND);
      matrix[XY((MATRIX_WIDTH - 1) - i, (MATRIX_HEIGHT - 1) - j)] = ColorFromPalette(currentPalette, map(j, 0, thisMax, 250, 0), 255, LINEARBLEND);
    }
  }
}
int peaks[16] = {};
void rainbowBars(int band, int barHeight)
{
  int xStart = BAR_WIDTH * band;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++)
  {
    for (int y = TOP; y >= TOP - barHeight; y--)
    {
      FastLedMatrix->drawPixel(x, y,
                               CHSV((x / BAR_WIDTH) * (255 / NUM_BANDS), 255, 255));
    }
  }
}
void whitePeak(int band)
{
  int xStart = BAR_WIDTH * band;
  int peakHeight = TOP - peaks[band] - 1;
  for (int x = xStart; x < xStart + BAR_WIDTH; x++)
  {
    FastLedMatrix->drawPixel(x, peakHeight, CHSV(0, 0, 255));
  }
}

void matrixSpectrum()
{
  FastLedMatrix->clear();
  for (int i = 0; i < NUM_BANDS; i++)
  {
    if (matrixValues[i] > peaks[i])
    {
      peaks[i] = matrixValues[i];
    }
    rainbowBars(i, matrixValues[i]);
    whitePeak(i);
    EVERY_N_MILLISECONDS(120)
    {
      for (byte band = 0; band < NUM_BANDS; band++)
      {
        if (peaks[band] > 0)
          peaks[band]--;
      }
    }
  }
}

void backgroundVuMatrix()
{
  int color = 0;
  for (byte band = 0; band < 8; band++)
  {
    if (matrixValues[band] > peaks[band])
    {
      peaks[band] = matrixValues[band];
    }
    for (int j = 0; j < 16; j++)
    {
      int aaa = j % 2 == 0 ? (NUM_BANDS * (j + 1)) - band - 1 : (NUM_BANDS * j) + band;
      int bbb = j % 2 == 0 ? 255 - ((NUM_BANDS * (j + 1)) - band - 1) : 255 - ((NUM_BANDS * j) + band);

      if (j < matrixValues[band])
      {
        matrix[aaa] = CHSV(color, 255, 255);
        matrix[bbb] = CHSV(color, 255, 255);
      }
      else
      {
        matrix[aaa] = CHSV(0, 0, 0);
        matrix[bbb] = CHSV(0, 0, 0);
      }

      // matrix[aaa] = (j < intensity) ? CHSV(color, 255, 255) : CHSV(0, 0, 0);
      // matrix[bbb] = (j < intensity) ? CHSV(color, 255, 255) : CHSV(0, 0, 0);
      if (j == peaks[band])
      {
        matrix[aaa] = CRGB::White;
        matrix[bbb] = CRGB::White;
      }
    }
    color += 255 / NUM_BANDS;

    EVERY_N_MILLISECONDS(120)
    {
      for (byte band = 0; band < NUM_BANDS; band++)
      {
        if (peaks[band] > 0)
          peaks[band]--;
      }
    }
  }
}
// DigitalRain_____________________________________
byte rain[NUM_LEDS_MATRIX];
int InitNeeded = 1;

void changepattern()
{
  int rand1 = random16(NUM_LEDS_MATRIX);
  int rand2 = random16(NUM_LEDS_MATRIX);
  if (rain[rand1] && !rain[rand2])
  {
    rain[rand1] = 0;
    rain[rand2] = 1;
  }
} // changepattern

void raininit()
{ // init array of dots. run once
  for (int i = 0; i < NUM_LEDS_MATRIX; i++)
    rain[i] = !random8(15) ? 1 : 0;
} // raininit

void updaterain()
{
  static int speed = 1;

  for (byte j = 0; j < MATRIX_HEIGHT; j++)
  {
    int yindex = (j + speed) % MATRIX_HEIGHT * MATRIX_WIDTH;
    for (byte i = 0; i < MATRIX_WIDTH; i++)
    {
      byte layer = rain[yindex + i];
      if (layer)
        matrix[XY((MATRIX_WIDTH - 1) - i, (MATRIX_HEIGHT - 1) - j)].setHue(100);
    }
  }

  fadeToBlackBy(matrix, 256, 70);
  speed++;
} // updaterain
void DigitalRain()
{
  if (InitNeeded)
  {
    raininit();
    InitNeeded = 0;
  }
  EVERY_N_MILLISECONDS(80) { updaterain(); }
  EVERY_N_MILLISECONDS(15) { changepattern(); }
}
byte dist(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  byte dist;
  int a = y2 - y1;
  int b = x2 - x1;
  a *= a;
  b *= b;
  a += b;
  dist = a ? 200 / sqrt16(a) : 200;
  return dist;
}
void metaballs()
{
  uint8_t bx1 = beatsin8(15, 0, MATRIX_WIDTH - 1, 0, 0);
  uint8_t by1 = beatsin8(18, 0, MATRIX_HEIGHT - 1, 0, 0);
  uint8_t bx2 = beatsin8(28, 0, MATRIX_WIDTH - 1, 0, 32);
  uint8_t by2 = beatsin8(23, 0, MATRIX_HEIGHT - 1, 0, 32);
  uint8_t bx3 = beatsin8(30, 0, MATRIX_WIDTH - 1, 0, 64);
  uint8_t by3 = beatsin8(24, 0, MATRIX_HEIGHT - 1, 0, 64);
  uint8_t bx4 = beatsin8(17, 0, MATRIX_WIDTH - 1, 0, 128);
  uint8_t by4 = beatsin8(25, 0, MATRIX_HEIGHT - 1, 0, 128);
  uint8_t bx5 = beatsin8(19, 0, MATRIX_WIDTH - 1, 0, 170);
  uint8_t by5 = beatsin8(21, 0, MATRIX_HEIGHT - 1, 0, 170);

  for (int i = 0; i < MATRIX_WIDTH; i++)
  {
    for (int j = 0; j < MATRIX_HEIGHT; j++)
    {
      byte sum = dist(i, j, bx1, by1);
      sum = qadd8(sum, dist(i, j, bx2, by2));
      sum = qadd8(sum, dist(i, j, bx3, by3));
      sum = qadd8(sum, dist(i, j, bx4, by4));
      sum = qadd8(sum, dist(i, j, bx5, by5));
      int index = XY(i, j);
      if (index != 256)
        matrix[XY(i, j)] = ColorFromPalette(HeatColors_p, qsub8(sum, 100), BRIGHTNESS);
    }
  }
}
void FireButterfly()
{
  uint16_t a = millis() / 2;

  for (int j = 0; j < MATRIX_HEIGHT; j++)
  {
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
      uint16_t index = XY(i, j);
      if (index != 256)
        matrix[index] = HeatColor(qsub8(inoise8(i * 80 + a, j * 5 + a, a / 3), abs8(j - (MATRIX_HEIGHT - 1)) * 255 / (MATRIX_HEIGHT + 3)));
    }
  }
}
void audioPlasma()
{
  static byte offset = 0;    // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center

  int xOffset = (cos8(plasVector / 256) - 127) / 2;
  int yOffset = (sin8(plasVector / 256) - 127) / 2;

  for (int x = 0; x < kMatrixWidth; x++)
  {
    for (int y = 0; y < kMatrixHeight; y++)
    {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 12 + xOffset) + sq(((float)y - 2) * 12 + yOffset)) + offset);
      matrix[XY(x, y)] = ColorFromPalette(Pal, color, 255);
    }
  }

  offset++;                                                                                                                                                           // wraps at 255 for sin8
  plasVector += (stripeValues[0] + stripeValues[1] + stripeValues[2] + stripeValues[3] + stripeValues[4] + stripeValues[5] + stripeValues[6] + stripeValues[7]) * 10; // using an int for slower orbit (wraps at 65536) //spectrumValue
  //  plasVector += (spectrumValue[1] + spectrumValue[2] + spectrumValue[3])/3;
} // audioPlasma()
void RedPeak()
{
  fadeToBlackBy(matrix, NUM_LEDS_MATRIX, 90);
  for (byte band = 0; band < NUM_BANDS; band++)
  {
    if (matrixValues[band] > peaks[band])
    {
      peaks[band] = matrixValues[band];
    }
    for (uint8_t i = 0; i < 16; i++)
    {
      if (i == peaks[band])
      {
        matrix[MatrixArray[band][i]] = CRGB::White;
        matrix[MatrixArrayFlip[band][i]] = CRGB::White;
      }
      int hue = map8(sin8(band) * 5, HUE_GREEN, HUE_MAX_SPECTRUM);

      if (i < matrixValues[band])
      {
        matrix[MatrixArray[band][i]] = CHSV(128, 0, 128);
        matrix[MatrixArrayFlip[band][i]] = CHSV(128, 0, 128);
      }
      else
      {
        // matrix[MatrixArray[band][i]] = CRGB::Black;
        // matrix[MatrixArrayFlip[band][i]] = CRGB::Black;
      }
    }
  }
  EVERY_N_MILLISECONDS(120)
  {
    for (byte band = 0; band < NUM_BANDS; band++)
    {
      if (peaks[band] < 16)
      {
        peaks[band]++;
      }
      else
      {
        if (matrixValues[band] > 1)
          peaks[band] = matrixValues[band];
      }
    }
  }
}
const PatternAndNameList patternsMatrix = {
    {RedPeak, "RedPeak", true},
    {audioPlasma, "audioPlasma", true},
    {FireButterfly, "FireButterfly", false},
    {metaballs, "metaballs", false},
    {DigitalRain, "digitalrain", false},
    {matrixSpectrum, "matrix", true},
    {backgroundVuMatrix, "background", true},
    {Twirl, "twirl", false},
    {Bands, "Bands", false},
    {Wave, "Wave", false},
    {Fire, "Fire", false},
    {aurora, "Aurora", false},
    {drop, "Drop", false},
    {Enoise, "Enoise", false},
    {bpmMatrix, "BPM Matrix", false}};

const uint8_t MatrixPatternsAmount = ARRAY_SIZE(patternsMatrix) - 1;