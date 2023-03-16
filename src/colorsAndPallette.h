#pragma once

#include "Imports.h"

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

DEFINE_GRADIENT_PALETTE(purple_gp){0, 0, 212, 255,         // blue
                                   255, 179, 0, 255};      // purple
DEFINE_GRADIENT_PALETTE(outrun_gp){0, 141, 0, 100,         // purple
                                   127, 255, 192, 0,       // yellow
                                   255, 0, 5, 255};        // blue
DEFINE_GRADIENT_PALETTE(greenblue_gp){0, 0, 255, 60,       // green
                                      64, 0, 236, 255,     // cyan
                                      128, 0, 5, 255,      // blue
                                      192, 0, 236, 255,    // cyan
                                      255, 0, 255, 60};    // green
DEFINE_GRADIENT_PALETTE(redyellow_gp){0, 200, 200, 200,    // white
                                      64, 255, 218, 0,     // yellow
                                      128, 231, 0, 0,      // red
                                      192, 255, 218, 0,    // yellow
                                      255, 200, 200, 200}; // white
CRGBPalette16 purplePal = purple_gp;
CRGBPalette16 outrunPal = outrun_gp;
CRGBPalette16 greenbluePal = greenblue_gp;
CRGBPalette16 heatPal = redyellow_gp;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PALETTES

// Gradient palette "YlOrBr_03_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/YlOrBr_03.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(YlOrBr_03_gp){0, 255, 237, 119, 84, 255, 237, 119,
                                      84, 252, 142, 13, 170, 252, 142, 13,
                                      170, 167, 29, 1, 255, 167, 29, 1};

// Gradient palette "RdPu_03_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/RdPu_03.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(RdPu_03_gp){0, 249, 191, 178, 84, 249, 191, 178,
                                    84, 242, 90, 108, 170, 242, 90, 108,
                                    170, 130, 1, 54, 255, 130, 1, 54};

// Gradient palette "BuGn_03_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/BuGn_03.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(BuGn_03_gp){0, 192, 233, 240, 84, 192, 233, 240,
                                    84, 67, 176, 140, 170, 67, 176, 140,
                                    170, 2, 93, 21, 255, 2, 93, 21};

// Gradient palette "GMT_panoply_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_panoply.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 128 bytes of program space.

DEFINE_GRADIENT_PALETTE(GMT_panoply_gp){
    0, 1, 1, 168, 15, 1, 1, 168, 15, 1, 19, 255, 31, 1, 19,
    255, 31, 7, 79, 255, 47, 7, 79, 255, 47, 27, 138, 255, 63, 27,
    138, 255, 63, 47, 178, 255, 79, 47, 178, 255, 79, 71, 219, 255, 95,
    71, 219, 255, 95, 95, 233, 255, 111, 95, 233, 255, 111, 146, 255, 255,
    127, 146, 255, 255, 127, 255, 252, 10, 143, 255, 252, 10, 143, 255, 213,
    0, 159, 255, 213, 0, 159, 255, 142, 0, 175, 255, 142, 0, 175, 255,
    72, 0, 191, 255, 72, 0, 191, 255, 15, 0, 207, 255, 15, 0, 207,
    255, 0, 0, 223, 255, 0, 0, 223, 159, 0, 0, 239, 159, 0, 0,
    239, 73, 0, 0, 255, 73, 0, 0};

// Gradient palette "pm3d07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pm/tn/pm3d07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(pm3d07_gp){0, 0, 255, 0, 84, 0, 32, 0,
                                   84, 255, 255, 0, 170, 135, 149, 0,
                                   170, 255, 0, 0, 255, 52, 0, 0};

// Gradient palette "Life_is_beautiful_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/colo/katiekat013/tn/Life_is_beautiful.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(Life_is_beautiful_gp){
    0, 2, 37, 16, 51, 2, 37, 16, 51, 3, 62, 11, 102, 3,
    62, 11, 102, 42, 68, 6, 153, 42, 68, 6, 153, 109, 112, 2,
    204, 109, 112, 2, 204, 242, 100, 0, 255, 242, 100, 0};

// Gradient palette "min_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/esdb/tn/min.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(min_gp){0, 255, 255, 0, 84, 255, 255, 0,
                                84, 101, 255, 45, 170, 101, 255, 45,
                                170, 42, 255, 255, 255, 42, 255, 255};

// Gradient palette "seismic_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gery/tn/seismic.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 216 bytes of program space.

DEFINE_GRADIENT_PALETTE(seismic_gp){
    0, 255, 4, 2, 40, 255, 4, 2, 40, 255, 34, 26, 61, 255, 34,
    26, 61, 255, 66, 54, 75, 255, 66, 54, 75, 255, 92, 80, 85, 255,
    92, 80, 85, 255, 115, 103, 92, 255, 115, 103, 92, 255, 135, 123, 98,
    255, 135, 123, 98, 255, 154, 144, 103, 255, 154, 144, 103, 255, 169, 160,
    108, 255, 169, 160, 108, 255, 186, 178, 112, 255, 186, 178, 112, 255, 201,
    194, 116, 255, 201, 194, 116, 255, 217, 212, 120, 255, 217, 212, 120, 255,
    231, 228, 123, 255, 231, 228, 123, 255, 246, 245, 127, 255, 246, 245, 127,
    255, 255, 255, 127, 255, 255, 255, 127, 247, 248, 255, 130, 247, 248, 255,
    130, 229, 233, 255, 134, 229, 233, 255, 134, 210, 217, 255, 138, 210, 217,
    255, 138, 194, 203, 255, 142, 194, 203, 255, 142, 177, 187, 255, 146, 177,
    187, 255, 146, 159, 171, 255, 150, 159, 171, 255, 150, 140, 154, 255, 156,
    140, 154, 255, 156, 121, 136, 255, 162, 121, 136, 255, 162, 100, 115, 255,
    169, 100, 115, 255, 169, 77, 92, 255, 179, 77, 92, 255, 179, 50, 65,
    255, 193, 50, 65, 255, 193, 23, 33, 255, 214, 23, 33, 255, 214, 2,
    4, 255, 255, 2, 4, 255};

// Gradient palette "Romanian_flag_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ggr/tn/Romanian_flag.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE(Romanian_flag_gp){
    0, 0, 0, 255, 42, 0, 0, 255, 84, 0, 0, 255,
    84, 255, 255, 0, 127, 255, 255, 0, 170, 255, 255, 0,
    170, 255, 0, 0, 212, 255, 0, 0, 255, 255, 0, 0};

// Gradient palette "cmy_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/imagej/tn/cmy.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 1052 bytes of program space.

DEFINE_GRADIENT_PALETTE(cmy_gp){
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 1, 0, 255,
    255, 2, 0, 255, 255, 3, 0, 255, 255, 4, 0, 255, 255, 5, 0,
    255, 255, 6, 0, 255, 255, 7, 0, 255, 255, 8, 0, 255, 255, 9,
    0, 255, 255, 10, 0, 255, 255, 11, 0, 255, 255, 12, 0, 255, 255,
    13, 0, 255, 255, 14, 0, 255, 255, 15, 0, 255, 255, 16, 0, 255,
    255, 17, 0, 255, 255, 18, 0, 255, 255, 19, 0, 255, 255, 20, 0,
    255, 255, 21, 0, 255, 255, 22, 0, 255, 255, 23, 0, 255, 255, 24,
    0, 255, 255, 25, 0, 255, 255, 26, 0, 255, 255, 27, 0, 255, 255,
    28, 0, 255, 255, 29, 0, 255, 255, 30, 0, 255, 255, 31, 0, 255,
    255, 32, 0, 255, 255, 33, 0, 255, 255, 34, 0, 255, 255, 35, 0,
    255, 255, 210, 255, 255, 0, 211, 255, 255, 0, 212, 255, 255, 0, 213,
    255, 255, 0, 214, 255, 255, 0, 215, 255, 255, 0, 216, 255, 255, 0,
    217, 255, 255, 0, 218, 255, 255, 0, 219, 255, 255, 0, 220, 255, 255,
    0, 221, 255, 255, 0, 222, 255, 255, 0, 223, 255, 255, 0, 224, 255,
    255, 0, 225, 255, 255, 0, 226, 255, 255, 0, 227, 255, 255, 0, 228,
    255, 255, 0, 229, 255, 255, 0, 230, 255, 255, 0, 231, 255, 255, 0,
    232, 255, 255, 0, 233, 255, 255, 0, 234, 255, 255, 0, 235, 255, 255,
    0, 236, 255, 255, 0, 237, 255, 255, 0, 238, 255, 255, 0, 239, 255,
    255, 0, 240, 255, 255, 0, 241, 255, 255, 0, 242, 255, 255, 0, 243,
    255, 255, 0, 244, 255, 255, 0, 245, 255, 255, 0, 246, 255, 255, 0,
    247, 255, 255, 0, 248, 255, 255, 0, 249, 255, 255, 0, 250, 255, 255,
    0, 251, 255, 255, 0, 252, 255, 255, 0, 252, 217, 223, 219, 253, 217,
    223, 219, 253, 237, 239, 237, 254, 237, 239, 237, 254, 255, 255, 255, 255,
    255, 255, 255};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PALETTES END

CRGBPalette16 palette1 = YlOrBr_03_gp;
CRGBPalette16 palette2 = RdPu_03_gp;
CRGBPalette16 palette3 = BuGn_03_gp;
CRGBPalette16 palette4 = GMT_panoply_gp;
CRGBPalette16 palette5 = pm3d07_gp;
CRGBPalette16 palette6 = Life_is_beautiful_gp;
CRGBPalette16 palette7 = min_gp;
CRGBPalette16 palette8 = seismic_gp;
CRGBPalette16 palette9 = Romanian_flag_gp;
CRGBPalette16 palette10 = cmy_gp;

CRGBPalette16 paletteList[] = {palette1, palette2, palette3, palette4,
                               palette5, palette6, palette7, palette8,
                               palette9, palette10};

int paletteIndex = 0;
CRGBPalette16 currentPalette = paletteList[paletteIndex];
CRGBPalette16 targetPalette = paletteList[paletteIndex];