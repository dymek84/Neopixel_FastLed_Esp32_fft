
#pragma once
#define stripethickness 33
#include "Imports.h"
#include "pgmspace.h"
#include "esp_Analyzer_Copy.h"

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
        matrix[r] = ColorFromPalette(currentPaletteMatrix, map(i, 0, 32, 255, 0), 255, LINEARBLEND);
      }
      else
      {
        matrix[r] = ColorFromPalette(currentPaletteMatrix, map(i, 0, 32, 0, 255), 255, LINEARBLEND);
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
      matrix[r] = ColorFromPalette(currentPaletteMatrix, map(i, 0, 32, 0, 255), 255, LINEARBLEND);
      if (delta >= 0 && delta < 127)
      {
        matrix[r] = ColorFromPalette(currentPaletteMatrix, map(i, 0, 32, 255, 0), 255, LINEARBLEND);
      }
      if (delta >= -255 && delta < -127)
      {
        matrix[r] = ColorFromPalette(currentPaletteMatrix, map(i, 0, 32, 255, 0), 255, LINEARBLEND);
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
      byte modulo = (i + j + colorHueMatrix) % stripethickness;
      modulo = map(modulo, 0, stripethickness, 0, 2); // reduces the 'bit depth'
      modulo = map(modulo, 0, 1, 0, 255);             // scales it back to full

      int r = (MatrixArray[j][i]);
      matrix[r] = ColorFromPalette(currentPaletteMatrix, modulo, 255, LINEARBLEND); // when modulo = 255 this gives colour 255,127,0 = orange; when it is 0, it is 0,0,255 = blue
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
      matrix[XY(x, y)] = ColorFromPalette(currentPaletteMatrix, pixelHue8 + ms / 20, 255, LINEARBLEND);
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
  fillAll(ColorFromPalette(currentPaletteMatrix, colorHueMatrix));

  for (uint8_t i = 0; i < ((MATRIX_HEIGHT + MATRIX_WIDTH) / 8) - 1; i++)
  {
    drawCircle(posx[i], posy[i], rad[i], ColorFromPalette(currentPaletteMatrix, (256 / 16) * 8.5 - rad[i] * 5 + colorHueMatrix));
    drawCircle(posx[i], posy[i], rad[i] - 1, ColorFromPalette(currentPaletteMatrix, (256 / 16) * 7.5 - rad[i] * 5 + colorHueMatrix));
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
          ColorFromPalette(currentPaletteMatrix,
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
    matrix[i] = ColorFromPalette(currentPaletteMatrix, colorHueMatrix + (i * 2), beat - colorHueMatrix + (i * 10));
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
      matrix[XY(i, j)] = ColorFromPalette(currentPaletteMatrix, map(j, 0, thisMax, 250, 0), 255, LINEARBLEND);
      matrix[XY((MATRIX_WIDTH - 1) - i, (MATRIX_HEIGHT - 1) - j)] = ColorFromPalette(currentPaletteMatrix, map(j, 0, thisMax, 250, 0), 255, LINEARBLEND);
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
    rain[i] = !random8(10) ? 1 : 0;
} // raininit

void updaterain()
{
  static int speed = 2;

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
bool rev[8];
void RedPeak2()
{
  fadeToBlackBy(matrix, NUM_LEDS_MATRIX, 40);
  for (byte band = 0; band < NUM_BANDS; band++)
  {
    if (matrixValues[band] > peaks[band])
    {
      // peaks[band] = matrixValues[band];
    }
    for (uint8_t i = 0; i < 32; i++)
    {
      int hue = colorHueMatrix + band * 8;
      if (i == peaks[band])
      {
        matrix[MatrixArray[band][i]] = CHSV(hue, 255, 255);
        matrix[MatrixArrayFlip[band][i]] = CHSV(hue, 255, 255);
      }

      if (i < matrixValues[band])
      {
        //  matrix[MatrixArray[band][i]] = CHSV(128, 0, 128);
        //  matrix[MatrixArrayFlip[band][i]] = CHSV(128, 0, 128);
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
      if (matrixValues[band] > 3)
      {
        if (peaks[band] < 31 && rev[band])
        {
          peaks[band]++;
        }
        if (peaks[band] > 0)
        {
          if (matrixValues[band] > 1)
          {
          }
          //    peaks[band] = matrixValues[band];
        }
        if (peaks[band] > 0 && !rev[band])
        {

          peaks[band]--;
        }
        if (peaks[band] == 0 || peaks[band] == 31)
        {
          rev[band] = !rev[band];
        }
      }
    }
  }
}
void MarqueeMirrored()
{
  static byte j = 0;
  j += 4;
  byte k = j;

  // Roughly equivalent to fill_rainbow(g_LEDs, NUM_LEDS, j, 8);

  CRGB c;
  for (int s = 0; s < MATRIX_HEIGHT; s++)
  {
    for (int i = 0; i < (MATRIX_WIDTH + 1) / 2; i++)
    {
      matrix[MatrixArray[s][i]] = ColorFromPalette(currentPaletteMatrix, k, 255);
      matrix[MatrixArray[s][MATRIX_WIDTH - 1 - i]] = ColorFromPalette(currentPaletteMatrix, k, 255);
      k += 8;
    }

    static int scroll = 0;
    scroll++;

    for (int i = scroll % 5; i < MATRIX_WIDTH / 2; i += 5)
    {
      //  matrix[MatrixArray[s][i]] = CRGB::Black;
      //  matrix[MatrixArray[s][MATRIX_WIDTH - 1 - i]] = CRGB::Black;
    }
  }
  minimumDelayFromPatternsMatrix(map(matrixValues[0], 0, 16, 100, 0)); // End Lightning Delay
}

#define maxMatrix 10

struct MatrixEffect
{
  float speed = float(random16(30, (NUM_LEDS_MATRIX)-10)) / (NUM_LEDS_MATRIX); // Random speed
  float ipos = NUM_LEDS_MATRIX - 1;                                            // Position of Head Led
  uint8_t endpos = random16(1, NUM_LEDS_MATRIX - (NUM_LEDS_MATRIX / 4));       // Random end position
  uint8_t lastpos;
  int stripNumber = 0;

  void InitMatrix()
  {
    speed = float(random16(50, (NUM_LEDS_MATRIX)-10)) / (NUM_LEDS_MATRIX); // Random speed

    ipos = NUM_LEDS_MATRIX - 1;                                    // Position of Head Led
    endpos = random16(1, NUM_LEDS_MATRIX - (NUM_LEDS_MATRIX / 4)); // Random end position
    stripNumber = random(0, MATRIX_HEIGHT);
  }
  void MoveMatrix()
  {
    for (int i = NUM_LEDS_MATRIX - 1; i > endpos; i--)
    {
      // g_LEDs[int(ipos)] += ColorFromPalette(currentPaletteMatrix, 1, 255, currentBlending);               // Draw Head
      matrix[MatrixArray[stripNumber][int(ipos)]] += ColorFromPalette(currentPaletteMatrix, random8(0, 16), random8(5, 50), LINEARBLEND);
      if (ipos < NUM_LEDS_MATRIX - 1)
      {
        matrix[MatrixArray[stripNumber][int(ipos + 1)]] = ColorFromPalette(currentPaletteMatrix, random8(0, 16), random8(5, 50), LINEARBLEND); // Draw Trail
        if (random8(255) > 244)
        {
          matrix[MatrixArray[stripNumber][int(ipos) + 1]] = CRGB(0, 0, 0); // Make random blanks on tail
        }
      }
    }
    ipos -= speed;
  }
}; // end of matrixeffect struct

MatrixEffect matrixEffect[maxMatrix];

void DrawMatrixEffect()
{
  //  currentPaletteMatrix = ForestColors_p;
  for (int i = 0; i < maxMatrix; i++)
  { // Reset Position and random speed at end position
    if (matrixEffect[i].ipos <= matrixEffect[i].endpos)
    { // and make head same as tail for fade to work
      matrix[MatrixArray[matrixEffect[i].stripNumber][int(matrixEffect[i].ipos + 1)]] = ColorFromPalette(currentPaletteMatrix, random8(0, 16), random8(5, 50), LINEARBLEND);
      matrixEffect[i].lastpos = matrixEffect[i].endpos;
      matrixEffect[i].InitMatrix();
    }
  }
  for (int i = 0; i < maxMatrix; i++)
  {
    matrixEffect[i].MoveMatrix();
  }
  EVERY_N_MILLISECONDS(150)
  {

    fadeToBlackBy(matrix, NUM_LEDS_MATRIX, 41);
  }
  //  delay(mappedMatrixInterval);
}

void fallingColorCreation(int freq)
{
  static int fallingBrightness;
  static int threshold = 10;
  int position = map(freq, 0, 8, 0, MATRIX_WIDTH - 1);
  if (matrixValues[freq] > threshold)
  {
    // constrain value between 0 and average + 3*stDev, map it to 0 - 255
    fallingBrightness = map(constrain(matrixValues[freq] * 16, 0, 255), 0, 200, 0, 255);
    fallingBrightness = constrain(fallingBrightness, 0, 255);
    // TODO: Make this work off of palettes
    for (uint8_t i = 0; i < 3; i++)
    {
      matrix[MatrixArrayFlip[MATRIX_HEIGHT - 1][position + i]] += CHSV(colorHueMatrix + freq * 30, 255, fallingBrightness);
    }
  }
}
void VirtualSnow()
{
  for (uint8_t x = 0U; x < WIDTH; x++)
  {
    for (uint8_t y = 0U; y < HEIGHT - 1; y++)
    {
      noise3d[0][x][y] = noise3d[0][x][y + 1];
      //  if (noise3d[0][x][y] > 0)
      if (matrixValues[0] > 6 && noise3d[0][x][y] > 0)
      {
        drawPixelXY(x, y, CHSV(170, 5U, 127 + (matrixValues[0] + matrixValues[7] + matrixValues[3]) * 5));
      }
    }
  }
  uint8_t posX = random(WIDTH);
  for (uint8_t x = 0U; x < WIDTH; x++)
  {
    // заполняем случайно верхнюю строку
    if (posX == x)
    {
      if (step % 3 == 0)
      {
        noise3d[0][x][HEIGHT - 1U] = 1;
      }
      else
      {
        noise3d[0][x][HEIGHT - 1U] = 0;
      }
    }
    else
    {
      noise3d[0][x][HEIGHT - 1U] = 0;
    }
  }
}
void fallingMusic()
{
  int i = random(MATRIX_WIDTH);
  matrix[MatrixArrayFlip[MATRIX_HEIGHT - 1][i]].nscale8(110);
  int jj = random(NUM_LEDS_MATRIX);
  matrix[jj].nscale8(110);
  // For every FFT bin, map the brightness of the light to the spectrumValue
  // TODO: Figure out why this for loop makes the LEDs all jittery and broken
  // for (int i = 0; i < 14; i++)
  //	fallingColorCreation(i);

  fallingColorCreation(0);
  fallingColorCreation(1);
  fallingColorCreation(2);
  fallingColorCreation(3);
  fallingColorCreation(4);
  fallingColorCreation(5);
  fallingColorCreation(6);
  fallingColorCreation(7);

  // Move all of the lights down
  EVERY_N_MILLIS(50)
  { // this slows the speed at which the lights fall
    for (int i = 0; i < 32; i++)
    { // for all the rows except the top one
      for (int j = 1; j < 7; j++)
      { // for all the columns
        //   matrix[MatrixArray[j][i]] = matrix[MatrixArray[j-1][i]]; // set the LED equal to the one above it
        matrix[MatrixArrayFlip[j][i]] = matrix[MatrixArrayFlip[j + 1][i]];
      }
    }
  }
}
void drawEffectnr2()
{
  CRGB temp;
  uint16_t _scale = map(scale, 1, 255, 30, adjScale);
  byte _speed = map(speed, 1, 255, 128, 16);
  for (byte x = 0; x < MATRIX_WIDTH; x++)
  {
    for (byte y = 0; y < MATRIX_HEIGHT; y++)
    {
      if (matrixValues[0] > 5)
      {
        // _scale += matrixValues[0] / 2;
        // VirtualSnow();
      }
      timer += matrixValues[0] / 2 + 3;
      matrix[XY(x, y)] = ColorFromPalette(currentPaletteMatrix,
                                          qsub8(inoise8(timer % 2 + x * _scale,
                                                        y * 16 + timer % 16,
                                                        timer / _speed),
                                                fabs((float)MATRIX_HEIGHT / 2 - (float)y) * adjastHeight));
    }
  }
  //  FastLED.delay(1); // ~ 60FPS
}

// =========== Christmas Tree ===========
//             © SlingMaster
//           EFF_CHRISTMAS_TREE
//            Новогодняя Елка
//---------------------------------------
void blurScreen(fract8 blur_amount, CRGB *LEDarray = matrix)
{
  blur2d(LEDarray, WIDTH, HEIGHT, blur_amount);
}
void dimAllmatrix(uint8_t value)
{
  // for (uint16_t i = 0; i < NUM_LEDS; i++) {
  //   leds[i].nscale8(value); //fadeToBlackBy
  // }
  //  теперь короткий вариант
  nscale8(matrix, NUM_LEDS_MATRIX, value);
  // fadeToBlackBy(LEDarray, NUM_LEDS, 255U - value); // эквивалент
}
uint32_t getPixColor(uint32_t thisSegm)
{
  uint32_t thisPixel = thisSegm; // * SEGMENTS;
  if (thisPixel > NUM_LEDS_MATRIX - 1)
    return 0;
  return (((uint32_t)matrix[thisPixel].r << 16) | ((uint32_t)matrix[thisPixel].g << 8) | (uint32_t)matrix[thisPixel].b); // а почему не просто return (leds[thisPixel])?
}
uint32_t getPixColorXY(uint8_t x, uint8_t y)
{
  return getPixColor(XY(x, y));
}
void StrobeAndDiffusion()
{
  const uint8_t SIZE = 1U;
  const uint8_t DELTA = 1U; // центровка по вертикали
  uint8_t STEP = 2U;
  if (loadingFlag)
  {
    loadingFlag = false;
    FPSdelay = 25U; // LOW_DELAY;
    hue2 = 1;
    FastLED.clear();
  }

  STEP = floor((255 - modes[currentMode].Speed) / 64) + 1U; // for strob
  if (modes[currentMode].Scale > 50)
  {
    // diffusion ---
    blurScreen(beatsin8(3, 64, 80));
    FPSdelay = LOW_DELAY;
    STEP = 1U;
    if (modes[currentMode].Scale < 75)
    {
      // chaos ---
      FPSdelay = 30;
      VirtualSnow();
    }
  }
  else
  {
    // strob -------
    if (modes[currentMode].Scale > 25)
    {
      dimAllmatrix(200);
      FPSdelay = 30;
    }
    else
    {
      dimAllmatrix(240);
      FPSdelay = 40;
    }
  }

  const uint8_t rows = (HEIGHT + 1) / 3U;
  deltaHue = floor(modes[currentMode].Speed / 64) * 64;
  bool dir = false;
  for (uint8_t y = 0; y < rows; y++)
  {
    if (dir)
    {
      if ((step % STEP) == 0)
      { // small layers
        drawPixelXY(WIDTH - 1, y * 3 + DELTA, CHSV(step, 255U, 255U));
      }
      else
      {
        drawPixelXY(WIDTH - 1, y * 3 + DELTA, CHSV(170U, 255U, 1U));
      }
    }
    else
    {
      if ((step % STEP) == 0)
      { // big layers
        drawPixelXY(0, y * 3 + DELTA, CHSV((step + deltaHue), 255U, 255U));
      }
      else
      {
        drawPixelXY(0, y * 3 + DELTA, CHSV(0U, 255U, 0U));
      }
    }

    // сдвигаем слои  ------------------
    for (uint8_t x = 0U; x < WIDTH; x++)
    {
      if (dir)
      { // <==
        drawPixelXY(x - 1, y * 3 + DELTA, getPixColorXY(x, y * 3 + DELTA));
      }
      else
      { // ==>
        drawPixelXY(WIDTH - x, y * 3 + DELTA, getPixColorXY(WIDTH - x - 1, y * 3 + DELTA));
      }
    }
    dir = !dir;
  }

  if (hue2 == 1)
  {
    step++;
    if (step >= 254)
      hue2 = 0;
  }
  else
  {
    step--;
    if (step < 1)
      hue2 = 1;
  }
  int cometSize = 1;
  int iPos = beatsin16(((stripeValues[7] / 10) + (stripeValues[1] / 10)) / 2, 0, NUM_LEDS_MATRIX - cometSize);
  byte hue = beatsin8(map(stripeValues[3], 0, 75, 2, 10));
  for (int i = iPos; i < iPos + cometSize; i++)
    matrix[i] = CHSV(hue, 255, map(stripeValues[0], 0, 75, 100, 255));

  int iPos2 = beatsin16(((stripeValues[0] / 10) + (stripeValues[6] / 10)) / 2, 0, NUM_LEDS_MATRIX - cometSize);
  byte hue2 = beatsin8(map(stripeValues[4], 0, 75, 2, 10));
  for (int i = iPos2; i < iPos2 + cometSize; i++)
    matrix[i] = CHSV(hue2, 255, map(stripeValues[7], 0, 75, 100, 255));
}

void backgroundVuMatrix2()
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

void changingBarsLS()
{
  for (int band = 0; band < numBands; band++)
  {
    changingBarsLS(band, matrixValues[band]);
  }
}

void TriBarLSTriPeakLS()
{
  for (int band = 0; band < numBands; band++)
  {
    TriBarLS(band, matrixValues[band]);
    TriPeakLS(band);
  }
}

void rainbowBarsLS()
{
  for (int band = 0; band < numBands; band++)
  {
    rainbowBarsLS(band, matrixValues[band]);
    NormalPeakLS(band, PeakColor1);
  }
}

void purpleBarsLS()
{
  for (int band = 0; band < numBands; band++)
  {
    purpleBarsLS(band, matrixValues[band]);
    NormalPeakLS(band, PeakColor2);
  }
}

void SameBarLS()
{
  for (int band = 0; band < numBands; band++)
  {
    SameBarLS(band, matrixValues[band]);
    NormalPeakLS(band, PeakColor3);
  }
}

void SameBar2LS()
{
  for (int band = 0; band < numBands; band++)
  {
    SameBar2LS(band, matrixValues[band]);
    NormalPeakLS(band, PeakColor3);
  }
}

void centerBarsLS()
{
  for (int band = 0; band < numBands; band++)
  {
    centerBarsLS(band, matrixValues[band]);
  }
}

void centerBars2LS()
{
  for (int band = 0; band < numBands; band++)
  {
    centerBars2LS(band, matrixValues[band]);
  }
}

void centerBars3LS()
{
  for (int band = 0; band < numBands; band++)
  {
    centerBars3LS(band, matrixValues[band]);
  }
}

void outrunPeakLS()
{
  for (int band = 0; band < numBands; band++)
  {
    BlackBarLS(band, matrixValues[band]);
    outrunPeakLS(band);
  }
}

void NormalPeakLS()
{
  for (int band = 0; band < numBands; band++)
  {
    BlackBarLS(band, matrixValues[band]);
    NormalPeakLS(band, PeakColor5);
  }
}

void BlackBarLS()
{
  for (int band = 0; band < numBands; band++)
  {
    BlackBarLS(band, matrixValues[band]);
    TriPeak2LS(band);
  }
}

const PatternAndNameList patternsMatrix = {
    {changingBarsLS, "changingBarsLS", true},
    {TriBarLSTriPeakLS, "TriBarLSTriPeakLS", true},
    {rainbowBarsLS, "rainbowBarsLS", true},
    {purpleBarsLS, "purpleBarsLS", true},
    {SameBarLS, "SameBarLS", true},
    {SameBar2LS, "SameBar2LS", true},
    {centerBarsLS, "centerBarsLS", true},
    {centerBars2LS, "centerBars2LS", true},
    {centerBars3LS, "centerBars3LS", true},
    {outrunPeakLS, "outrunPeakLS", true},
    {NormalPeakLS, "NormalPeakLS", true},
    {BlackBarLS, "BlackBarLS", true},
    {drawEffectnr2, "Draw Effectnr2", true},
    {matrixSpectrum, "Matrix Spectrum", true},
    {backgroundVuMatrix, "Background", true},
    {backgroundVuMatrix2, "Horizontal Lines", true},
    {fallingMusic, "Falling Colors", true},
    {DrawMatrixEffect, "Draw Matrix Effect", false},
    {RedPeak, "Blurred Peak", true},
    {RedPeak2, "Colored Peak", true},
    {audioPlasma, "Audio Plasma", true},
    {MarqueeMirrored, "Marquee Mirrored", false},
    {FireButterfly, "Fire Butterfly", false},
    {metaballs, "Meta Balls", false},
    {DigitalRain, "Digital Rain", false},
    {StrobeAndDiffusion, "Strobe And Diffusion", false},
    {Twirl, "Twirl", false},
    {Bands, "Bands", false},
    {Wave, "Wave", false},
    {Fire, "Fire", false},
    {aurora, "Aurora", false},
    {drop, "Drop", false},
    {Enoise, "Enoise", false},
    {bpmMatrix, "BPM Matrix", false}};

const uint8_t MatrixPatternsAmount = ARRAY_SIZE(patternsMatrix) - 1;
