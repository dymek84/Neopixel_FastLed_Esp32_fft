
#ifndef _CLOCK_INO__
#define _CLOCK_INO__

#include "Imports.h"

int druga[]{94, 97, 110, 113, 114, 115, 116, 107, 100, 91, 90, 89, 88, 103, 104, 119};
int trzecia[]{94, 97, 110, 113, 114, 115, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119};
int czwarta[]{94, 113, 114, 115, 116, 107, 100, 91, 92, 93, 117, 118, 119};
int piata[]{94, 97, 110, 113, 92, 93, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119};
int szusta[]{94, 97, 110, 113, 92, 93, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119, 90, 89};
int siudma[]{94, 97, 110, 113, 114, 108, 107, 101, 102, 103};
int osma[]{92, 93, 94, 97, 110, 113, 114, 115, 116, 117, 118, 107, 100, 91, 90, 89, 88, 103, 104, 119};
int dziewiata[]{94, 97, 110, 113, 92, 93, 114, 115, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119};
int dziesiata[]{94, 97, 110, 113, 114, 115, 116, 117, 118, 92, 93, 91, 90, 89, 88, 103, 104, 119, 72, 73, 74, 75, 76, 77, 78};
int jedenasta[]{113, 114, 115, 116, 117, 118, 119, 72, 73, 74, 75, 76, 77, 78};
int dwunasta[]{94, 97, 110, 113, 114, 115, 116, 107, 100, 91, 90, 89, 88, 103, 104, 119, 72, 73, 74, 75, 76, 77, 78};
int trzynasta[]{94, 97, 110, 113, 114, 115, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119, 72, 73, 74, 75, 76, 77, 78};
int czternasta[]{94, 113, 114, 115, 116, 107, 100, 91, 92, 93, 117, 118, 119, 72, 73, 74, 75, 76, 77, 78};
int pietnasta[]{94, 97, 110, 113, 92, 93, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119, 72, 73, 74, 75, 76, 77, 78};
int szesnasta[]{94, 97, 110, 113, 92, 93, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119, 90, 89, 72, 73, 74, 75, 76, 77, 78};
int siedemnasta[]{94, 97, 110, 113, 114, 108, 107, 101, 102, 103, 72, 73, 74, 75, 76, 77, 78};
int osiemnasta[]{92, 93, 94, 97, 110, 113, 114, 115, 116, 117, 118, 107, 100, 91, 90, 89, 88, 103, 104, 119, 72, 73, 74, 75, 76, 77, 78};
int dziewietnasta[]{94, 97, 110, 113, 92, 93, 114, 115, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119, 72, 73, 74, 75, 76, 77, 78};
int dwudziesta[]{49, 62, 65, 78, 77, 76, 75, 68, 59, 52, 53, 54, 55, 56, 71, 72, 88, 89, 90, 91, 92, 93, 94, 97, 110, 113, 114, 115, 116, 117, 118, 119, 104, 103};
int dwudziestapierwsza[]{49, 62, 65, 78, 77, 76, 75, 68, 59, 52, 53, 54, 55, 56, 71, 72, 113, 114, 115, 116, 117, 118, 119};

int dwudziestadruga[]{94, 97, 110, 113, 114, 115, 116, 107, 100, 91, 90, 89, 88, 103, 104, 119, 49, 62, 65, 78, 77, 76, 75, 68, 59, 52, 53, 54, 55, 56, 71, 72};
int dwudziestatrzecia[]{94, 97, 110, 113, 114, 115, 116, 107, 100, 91, 117, 118, 88, 103, 104, 119, 49, 62, 65, 78, 77, 76, 75, 68, 59, 52, 53, 54, 55, 56, 71, 72};
int polnoc[]{88, 89, 90, 91, 92, 93, 94, 97, 110, 113, 114, 115, 116, 117, 118, 119, 104, 103};

int minPierwszaZero[]{168, 169, 170, 171, 172, 173, 174, 161, 158, 145, 146, 147, 148, 149, 150, 151, 152, 167};
int minPierwszaJeden[]{168, 169, 170, 171, 172, 173, 174};
int minPierwszaDwa[]{145, 158, 161, 174, 173, 172, 171, 164, 155, 148, 149, 150, 151, 152, 167, 168};
int minPierwszaTrzy[]{145, 158, 161, 174, 173, 172, 171, 164, 155, 148, 170, 169, 151, 152, 167, 168};
int minPierwszaCztery[]{145, 146, 147, 148, 174, 173, 172, 171, 164, 155, 148, 171, 170, 169, 168};
int minPierwszaPiec[]{145, 158, 161, 174, 146, 147, 171, 164, 155, 148, 170, 169, 151, 152, 167, 168};
int minPierwszaSzejsc[]{145, 158, 161, 174, 146, 147, 171, 164, 155, 148, 170, 169, 151, 152, 167, 168, 149, 150};
int minPierwszaSiedem[]{145, 158, 161, 174, 173, 163, 164, 154, 153, 152};
int minPierwszaOsiem[]{145, 158, 161, 174, 173, 172, 171, 164, 155, 148, 170, 169, 151, 152, 167, 168, 146, 147, 149, 150};
int minPierwszaDziewiec[]{145, 158, 161, 174, 173, 172, 171, 164, 155, 148, 170, 169, 151, 152, 167, 168, 146, 147};

int celciusz[]{193, 206, 209, 210, 211, 204, 195, 194};
int clockColor = 0;
int sat = 0;
void clock(int hour, int min, boolean menu, int menuname, int percent)
{

    menu ? clockColor = 255 : clockColor = 0;
    menu ? sat = 255 : sat = 0;

    long Seconds = millis() / 1000;
    if (!menu)
    {
        if (Seconds % 2 == 0)
        {
            matrix[130] = CHSV(0, 0, 0);
            matrix[134] = CHSV(0, 0, 0);
        }
        else
        {

            matrix[130] = CHSV(clockColor, sat, chageClockBright);
            matrix[134] = CHSV(clockColor, sat, chageClockBright);
        }
    }
    if (menuname == 0)
    {
        if (min < 10)
        {
            for (int i = 0; i < sizeof minPierwszaZero / sizeof minPierwszaZero[0]; i++)
            {
                // int s = ;
                matrix[minPierwszaZero[i]] = CHSV(clockColor, sat, chageClockBright);
            }
            if (min == 0)
            {
                for (int i = 0; i < sizeof minPierwszaZero / sizeof minPierwszaZero[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaZero[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 1)
            {
                for (int i = 0; i < sizeof minPierwszaJeden / sizeof minPierwszaJeden[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaJeden[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 2)
            {
                for (int i = 0; i < sizeof minPierwszaDwa / sizeof minPierwszaDwa[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaDwa[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 3)
            {
                for (int i = 0; i < sizeof minPierwszaTrzy / sizeof minPierwszaTrzy[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaTrzy[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 4)
            {
                for (int i = 0; i < sizeof minPierwszaCztery / sizeof minPierwszaCztery[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaCztery[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 5)
            {
                for (int i = 0; i < sizeof minPierwszaPiec / sizeof minPierwszaPiec[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaPiec[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 6)
            {
                for (int i = 0; i < sizeof minPierwszaSzejsc / sizeof minPierwszaSzejsc[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaSzejsc[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 7)
            {
                for (int i = 0; i < sizeof minPierwszaSiedem / sizeof minPierwszaSiedem[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaSiedem[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 8)
            {
                for (int i = 0; i < sizeof minPierwszaOsiem / sizeof minPierwszaOsiem[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaOsiem[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (min == 9)
            {
                for (int i = 0; i < sizeof minPierwszaDziewiec / sizeof minPierwszaDziewiec[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaDziewiec[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
        }
        else if (min >= 10)
        {
            // int n = 12345; // or whatever number

            int druga = min % 10;
            int pierwsza = (min / 10) % 10;
            if (pierwsza == 0)
            {
                for (int i = 0; i < sizeof minPierwszaZero / sizeof minPierwszaZero[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaZero[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 1)
            {
                for (int i = 0; i < sizeof minPierwszaJeden / sizeof minPierwszaJeden[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaJeden[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 2)
            {
                for (int i = 0; i < sizeof minPierwszaDwa / sizeof minPierwszaDwa[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaDwa[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 3)
            {
                for (int i = 0; i < sizeof minPierwszaTrzy / sizeof minPierwszaTrzy[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaTrzy[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 4)
            {
                for (int i = 0; i < sizeof minPierwszaCztery / sizeof minPierwszaCztery[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaCztery[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 5)
            {
                for (int i = 0; i < sizeof minPierwszaPiec / sizeof minPierwszaPiec[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaPiec[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 6)
            {
                for (int i = 0; i < sizeof minPierwszaSzejsc / sizeof minPierwszaSzejsc[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaSzejsc[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 7)
            {
                for (int i = 0; i < sizeof minPierwszaSiedem / sizeof minPierwszaSiedem[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaSiedem[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 8)
            {
                for (int i = 0; i < sizeof minPierwszaOsiem / sizeof minPierwszaOsiem[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaOsiem[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (pierwsza == 9)
            {
                for (int i = 0; i < sizeof minPierwszaDziewiec / sizeof minPierwszaDziewiec[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaDziewiec[i]] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            if (druga == 0)
            {
                for (int i = 0; i < sizeof minPierwszaZero / sizeof minPierwszaZero[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaZero[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 1)
            {
                for (int i = 0; i < sizeof minPierwszaJeden / sizeof minPierwszaJeden[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaJeden[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 2)
            {
                for (int i = 0; i < sizeof minPierwszaDwa / sizeof minPierwszaDwa[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaDwa[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 3)
            {
                for (int i = 0; i < sizeof minPierwszaTrzy / sizeof minPierwszaTrzy[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaTrzy[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 4)
            {
                for (int i = 0; i < sizeof minPierwszaCztery / sizeof minPierwszaCztery[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaCztery[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 5)
            {
                for (int i = 0; i < sizeof minPierwszaPiec / sizeof minPierwszaPiec[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaPiec[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 6)
            {
                for (int i = 0; i < sizeof minPierwszaSzejsc / sizeof minPierwszaSzejsc[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaSzejsc[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 7)
            {
                for (int i = 0; i < sizeof minPierwszaSiedem / sizeof minPierwszaSiedem[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaSiedem[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 8)
            {
                for (int i = 0; i < sizeof minPierwszaOsiem / sizeof minPierwszaOsiem[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaOsiem[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
            else if (druga == 9)
            {
                for (int i = 0; i < sizeof minPierwszaDziewiec / sizeof minPierwszaDziewiec[0]; i++)
                {
                    // int s = ;
                    matrix[minPierwszaDziewiec[i] + 48] = CHSV(clockColor, sat, chageClockBright);
                }
            }
        }

        if (hour == 1)
        {
            for (int i = 113; i <= 119; i++)
            {
                matrix[i] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 2)
        {
            for (int i = 0; i < sizeof druga / sizeof druga[0]; i++)
            {
                // int s = ;
                matrix[druga[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 3)
        {
            for (int i = 0; i < sizeof trzecia / sizeof trzecia[0]; i++)
            {
                // int s = ;
                matrix[trzecia[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 4)
        {
            for (int i = 0; i < sizeof czwarta / sizeof czwarta[0]; i++)
            {
                // int s = ;
                matrix[czwarta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 5)
        {
            for (int i = 0; i < sizeof piata / sizeof piata[0]; i++)
            {
                // int s = ;
                matrix[piata[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 6)
        {
            for (int i = 0; i < sizeof szusta / sizeof szusta[0]; i++)
            {
                // int s = ;
                matrix[szusta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 7)
        {
            for (int i = 0; i < sizeof siudma / sizeof siudma[0]; i++)
            {
                // int s = ;
                matrix[siudma[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 8)
        {
            for (int i = 0; i < sizeof osma / sizeof osma[0]; i++)
            {
                // int s = ;
                matrix[osma[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 9)
        {
            for (int i = 0; i < sizeof dziewiata / sizeof dziewiata[0]; i++)
            {
                // int s = ;
                matrix[dziewiata[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 10)
        {
            for (int i = 0; i < sizeof dziesiata / sizeof dziesiata[0]; i++)
            {
                // int s = ;
                matrix[dziesiata[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 11)
        {
            for (int i = 0; i < sizeof jedenasta / sizeof jedenasta[0]; i++)
            {
                // int s = ;
                matrix[jedenasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 12)
        {
            for (int i = 0; i < sizeof dwunasta / sizeof dwunasta[0]; i++)
            {
                // int s = ;
                matrix[dwunasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 13)
        {
            for (int i = 0; i < sizeof trzynasta / sizeof trzynasta[0]; i++)
            {
                // int s = ;
                matrix[trzynasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 14)
        {
            for (int i = 0; i < sizeof czternasta / sizeof czternasta[0]; i++)
            {
                // int s = ;
                matrix[czternasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 15)
        {
            for (int i = 0; i < sizeof pietnasta / sizeof pietnasta[0]; i++)
            {
                // int s = ;
                matrix[pietnasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 16)
        {
            for (int i = 0; i < sizeof szesnasta / sizeof szesnasta[0]; i++)
            {
                // int s = ;
                matrix[szesnasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 17)
        {
            for (int i = 0; i < sizeof siedemnasta / sizeof siedemnasta[0]; i++)
            {
                // int s = ;
                matrix[siedemnasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 18)
        {
            for (int i = 0; i < sizeof osiemnasta / sizeof osiemnasta[0]; i++)
            {
                // int s = ;
                matrix[osiemnasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 19)
        {
            for (int i = 0; i < sizeof dziewietnasta / sizeof dziewietnasta[0]; i++)
            {
                // int s = ;
                matrix[dziewietnasta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 20)
        {
            for (int i = 0; i < sizeof dwudziesta / sizeof dwudziesta[0]; i++)
            {
                // int s = ;
                matrix[dwudziesta[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 21)
        {
            for (int i = 0; i < sizeof dwudziestapierwsza / sizeof dwudziestapierwsza[0]; i++)
            {
                // int s = ;
                matrix[dwudziestapierwsza[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 22)
        {
            for (int i = 0; i < sizeof dwudziestadruga / sizeof dwudziestadruga[0]; i++)
            {
                // int s = ;
                matrix[dwudziestadruga[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 23)
        {
            for (int i = 0; i < sizeof dwudziestatrzecia / sizeof dwudziestatrzecia[0]; i++)
            {
                // int s = ;
                matrix[dwudziestatrzecia[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        else if (hour == 0)
        {
            for (int i = 0; i < sizeof polnoc / sizeof polnoc[0]; i++)
            {
                // int s = ;
                matrix[polnoc[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
    }
    else
    {

        int LedBrightness[]{49, 50, 51, 52, 53, 54, 55, 56, 71, 72, 88, 89, 90, 91, 92, 93, 94, 97, 110, 114, 115, 100, 107, 117, 118, 104, 103};
        int chageClockBrightness[]{77, 65, 62, 50, 51, 52, 53, 54, 56, 71, 73, 88, 89, 90, 91, 92, 93, 94, 97, 110, 114, 115, 100, 107, 117, 118, 104, 103};
        int colorName[]{77, 65, 62, 50, 51, 52, 53, 54, 56, 71, 73};
        int speedName[]{77, 65, 62, 50, 51, 59, 68, 74, 73, 71, 56, 54};
        showPercent(percentage);
        if (menuname == 1)
        {
            for (int i = 0; i < sizeof LedBrightness / sizeof LedBrightness[0]; i++)
            {
                matrix[LedBrightness[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        if (menuname == 2)
        {
            for (int i = 0; i < sizeof colorName / sizeof colorName[0]; i++)
            {
                matrix[colorName[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        if (menuname == 3)
        {
            for (int i = 0; i < sizeof speedName / sizeof speedName[0]; i++)
            {
                matrix[speedName[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
        if (menuname == 4)
        {
            for (int i = 0; i < sizeof chageClockBrightness / sizeof chageClockBrightness[0]; i++)
            {
                matrix[chageClockBrightness[i]] = CHSV(clockColor, sat, chageClockBright);
            }
        }
    }
}
void showPercent(int value)
{
    int procenty1[]{135};
    int procenty2[]{135, 136, 137};
    int procenty3[]{135, 136, 137, 149, 150, 151};
    int procenty4[]{135, 136, 137, 149, 150, 151, 152, 153, 154, 155};
    int procenty5[]{135, 136, 137, 149, 150, 151, 152, 153, 154, 155, 163, 164, 165, 166, 167};
    int procenty6[]{135, 136, 137, 149, 150, 151, 152, 153, 154, 155, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173};
    int procenty7[]{135, 136, 137, 149, 150, 151, 152, 153, 154, 155, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 177, 178, 179, 180, 181, 182, 183};
    int procenty8[]{135, 136, 137, 149, 150, 151, 152, 153, 154, 155, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191};
    if (value == 0)
    {
        for (int i = 0; i < sizeof procenty1 / sizeof procenty1[0]; i++)
        {
            matrix[procenty1[i]] = CHSV(255, sat, chageClockBright);
        }
    }
    if (value == 1)
    {
        for (int i = 0; i < sizeof procenty1 / sizeof procenty1[0]; i++)
        {
            matrix[procenty1[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 2)
    {
        for (int i = 0; i < sizeof procenty2 / sizeof procenty2[0]; i++)
        {
            matrix[procenty2[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 3)
    {
        for (int i = 0; i < sizeof procenty3 / sizeof procenty3[0]; i++)
        {
            matrix[procenty3[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 4)
    {
        for (int i = 0; i < sizeof procenty4 / sizeof procenty4[0]; i++)
        {
            matrix[procenty4[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 5)
    {
        for (int i = 0; i < sizeof procenty5 / sizeof procenty5[0]; i++)
        {
            matrix[procenty5[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 6)
    {
        for (int i = 0; i < sizeof procenty6 / sizeof procenty6[0]; i++)
        {
            matrix[procenty6[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 7)
    {
        for (int i = 0; i < sizeof procenty7 / sizeof procenty7[0]; i++)
        {
            matrix[procenty7[i]] = CHSV(125, sat, chageClockBright);
        }
    }
    if (value == 8)
    {
        for (int i = 0; i < sizeof procenty8 / sizeof procenty8[0]; i++)
        {
            matrix[procenty8[i]] = CHSV(125, sat, chageClockBright);
        }
    }
}
#endif