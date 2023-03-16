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

// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.

// Gradient palette "ib_jul01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(ib_jul01_gp){0, 194, 1, 1, 94, 1, 29, 18, 132, 57, 131, 28, 255, 113, 1, 1};
DEFINE_GRADIENT_PALETTE(es_vintage_57_gp){0, 2, 1, 1, 53, 18, 1, 0, 104, 69, 29, 1, 153, 167, 135, 10, 255, 46, 56, 4};
DEFINE_GRADIENT_PALETTE(es_vintage_01_gp){0, 4, 1, 1, 51, 16, 0, 1, 76, 97, 104, 3, 101, 255, 131, 19, 127, 67, 9, 4, 153, 16, 0, 1, 229, 4, 1, 1, 255, 4, 1, 1};
DEFINE_GRADIENT_PALETTE(es_rivendell_15_gp){0, 1, 14, 5, 101, 16, 36, 14, 165, 56, 68, 30, 242, 150, 156, 99, 255, 150, 156, 99};
DEFINE_GRADIENT_PALETTE(rgi_15_gp){0, 4, 1, 31, 31, 55, 1, 16, 63, 197, 3, 7, 95, 59, 2, 17, 127, 6, 2, 34, 159, 39, 6, 33, 191, 112, 13, 32, 223, 56, 9, 35, 255, 22, 6, 38};
DEFINE_GRADIENT_PALETTE(retro2_16_gp){0, 188, 135, 1, 255, 46, 7, 1};
DEFINE_GRADIENT_PALETTE(Analogous_1_gp){0, 3, 0, 255, 63, 23, 0, 255, 127, 67, 0, 255, 191, 142, 0, 45, 255, 255, 0, 0};
DEFINE_GRADIENT_PALETTE(es_pinksplash_08_gp){0, 126, 11, 255, 127, 197, 1, 22, 175, 210, 157, 172, 221, 157, 3, 112, 255, 157, 3, 112};
DEFINE_GRADIENT_PALETTE(es_pinksplash_07_gp){0, 229, 1, 1, 61, 242, 4, 63, 101, 255, 12, 255, 127, 249, 81, 252, 153, 255, 11, 235, 193, 244, 5, 68, 255, 232, 1, 5};
DEFINE_GRADIENT_PALETTE(Coral_reef_gp){0, 40, 199, 197, 50, 10, 152, 155, 96, 1, 111, 120, 96, 43, 127, 162, 139, 10, 73, 111, 255, 1, 34, 71};
DEFINE_GRADIENT_PALETTE(es_ocean_breeze_068_gp){0, 100, 156, 153, 51, 1, 99, 137, 101, 1, 68, 84, 104, 35, 142, 168, 178, 0, 63, 117, 255, 1, 10, 10};
DEFINE_GRADIENT_PALETTE(es_ocean_breeze_036_gp){0, 1, 6, 7, 89, 1, 99, 111, 153, 144, 209, 255, 255, 0, 73, 82};
DEFINE_GRADIENT_PALETTE(departure_gp){0, 8, 3, 0, 42, 23, 7, 0, 63, 75, 38, 6, 84, 169, 99, 38, 106, 213, 169, 119, 116, 255, 255, 255, 138, 135, 255, 138, 148, 22, 255, 24, 170, 0, 255, 0, 191, 0, 136, 0, 212, 0, 55, 0, 255, 0, 55, 0};
DEFINE_GRADIENT_PALETTE(es_landscape_64_gp){0, 0, 0, 0, 37, 2, 25, 1, 76, 15, 115, 5, 127, 79, 213, 1, 128, 126, 211, 47, 130, 188, 209, 247, 153, 144, 182, 205, 204, 59, 117, 250, 255, 1, 37, 192};
DEFINE_GRADIENT_PALETTE(es_landscape_33_gp){0, 1, 5, 0, 19, 32, 23, 1, 38, 161, 55, 1, 63, 229, 144, 1, 66, 39, 142, 74, 255, 1, 4, 1};
DEFINE_GRADIENT_PALETTE(rainbowsherbet_gp){0, 255, 33, 4, 43, 255, 68, 25, 86, 255, 7, 25, 127, 255, 82, 103, 170, 255, 255, 242, 209, 42, 255, 22, 255, 87, 255, 65};
DEFINE_GRADIENT_PALETTE(gr65_hult_gp){0, 247, 176, 247, 48, 255, 136, 255, 89, 220, 29, 226, 160, 7, 82, 178, 216, 1, 124, 109, 255, 1, 124, 109};
DEFINE_GRADIENT_PALETTE(gr64_hult_gp){0, 1, 124, 109, 66, 1, 93, 79, 104, 52, 65, 1, 130, 115, 127, 1, 150, 52, 65, 1, 201, 1, 86, 72, 239, 0, 55, 45, 255, 0, 55, 45};
DEFINE_GRADIENT_PALETTE(GMT_drywet_gp){0, 47, 30, 2, 42, 213, 147, 24, 84, 103, 219, 52, 127, 3, 219, 207, 170, 1, 48, 214, 212, 1, 1, 111, 255, 1, 7, 33};
DEFINE_GRADIENT_PALETTE(ib15_gp){0, 113, 91, 147, 72, 157, 88, 78, 89, 208, 85, 33, 107, 255, 29, 11, 141, 137, 31, 39, 255, 59, 33, 89};
DEFINE_GRADIENT_PALETTE(Fuschia_7_gp){0, 43, 3, 153, 63, 100, 4, 103, 127, 188, 5, 66, 191, 161, 11, 115, 255, 135, 20, 182};
DEFINE_GRADIENT_PALETTE(es_emerald_dragon_08_gp){0, 97, 255, 1, 101, 47, 133, 1, 178, 13, 43, 1, 255, 2, 10, 1};
DEFINE_GRADIENT_PALETTE(lava_gp){0, 0, 0, 0, 46, 18, 0, 0, 96, 113, 0, 0, 108, 142, 3, 1, 119, 175, 17, 1, 146, 213, 44, 2, 174, 255, 82, 4, 188, 255, 115, 4, 202, 255, 156, 4, 218, 255, 203, 4, 234, 255, 255, 4, 244, 255, 255, 71, 255, 255, 255, 255};
DEFINE_GRADIENT_PALETTE(fire_gp){0, 1, 1, 0, 76, 32, 5, 0, 146, 192, 24, 0, 197, 220, 105, 5, 240, 252, 255, 31, 250, 252, 255, 111, 255, 255, 255, 255};
DEFINE_GRADIENT_PALETTE(Colorfull_gp){0, 10, 85, 5, 25, 29, 109, 18, 60, 59, 138, 42, 93, 83, 99, 52, 106, 110, 66, 64, 109, 123, 49, 65, 113, 139, 35, 66, 116, 192, 117, 98, 124, 255, 255, 137, 168, 100, 180, 155, 255, 22, 121, 174};
DEFINE_GRADIENT_PALETTE(Magenta_Evening_gp){0, 71, 27, 39, 31, 130, 11, 51, 63, 213, 2, 64, 70, 232, 1, 66, 76, 252, 1, 69, 108, 123, 2, 51, 255, 46, 9, 35};
DEFINE_GRADIENT_PALETTE(Pink_Purple_gp){0, 19, 2, 39, 25, 26, 4, 45, 51, 33, 6, 52, 76, 68, 62, 125, 102, 118, 187, 240, 109, 163, 215, 247, 114, 217, 244, 255, 122, 159, 149, 221, 149, 113, 78, 188, 183, 128, 57, 155, 255, 146, 40, 123};
DEFINE_GRADIENT_PALETTE(Sunset_Real_gp){0, 120, 0, 0, 22, 179, 22, 0, 51, 255, 104, 0, 85, 167, 22, 18, 135, 100, 0, 103, 198, 16, 0, 130, 255, 0, 0, 160};
DEFINE_GRADIENT_PALETTE(es_autumn_19_gp){0, 26, 1, 1, 51, 67, 4, 1, 84, 118, 14, 1, 104, 137, 152, 52, 112, 113, 65, 1, 122, 133, 149, 59, 124, 137, 152, 52, 135, 113, 65, 1, 142, 139, 154, 46, 163, 113, 13, 1, 204, 55, 3, 1, 249, 17, 1, 1, 255, 17, 1, 1};
DEFINE_GRADIENT_PALETTE(BlacK_Blue_Magenta_White_gp){0, 0, 0, 0, 42, 0, 0, 45, 84, 0, 0, 255, 127, 42, 0, 255, 170, 255, 0, 255, 212, 255, 55, 255, 255, 255, 255, 255};
DEFINE_GRADIENT_PALETTE(BlacK_Magenta_Red_gp){0, 0, 0, 0, 63, 42, 0, 45, 127, 255, 0, 255, 191, 255, 0, 45, 255, 255, 0, 0};
DEFINE_GRADIENT_PALETTE(BlacK_Red_Magenta_Yellow_gp){0, 0, 0, 0, 42, 42, 0, 0, 84, 255, 0, 0, 127, 255, 0, 45, 170, 255, 0, 255, 212, 255, 55, 45, 255, 255, 255, 0};
DEFINE_GRADIENT_PALETTE(Blue_Cyan_Yellow_gp){0, 0, 0, 255, 63, 0, 55, 255, 127, 0, 255, 255, 191, 42, 255, 45, 255, 255, 255, 0};

const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
    Sunset_Real_gp,
    es_rivendell_15_gp,
    es_ocean_breeze_036_gp,
    rgi_15_gp,
    retro2_16_gp,
    Analogous_1_gp,
    es_pinksplash_08_gp,
    Coral_reef_gp,
    es_ocean_breeze_068_gp,
    es_pinksplash_07_gp,
    es_vintage_01_gp,
    departure_gp,
    es_landscape_64_gp,
    es_landscape_33_gp,
    rainbowsherbet_gp,
    gr65_hult_gp,
    gr64_hult_gp,
    GMT_drywet_gp,
    ib_jul01_gp,
    es_vintage_57_gp,
    ib15_gp,
    Fuschia_7_gp,
    es_emerald_dragon_08_gp,
    lava_gp,
    fire_gp,
    Colorfull_gp,
    Magenta_Evening_gp,
    Pink_Purple_gp,
    es_autumn_19_gp,
    BlacK_Blue_Magenta_White_gp,
    BlacK_Magenta_Red_gp,
    BlacK_Red_Magenta_Yellow_gp,
    Blue_Cyan_Yellow_gp};

// Count of how many cpt-city gradients are defined:
const uint8_t gGradientPaletteCount =
    sizeof(gGradientPalettes) / sizeof(TProgmemRGBGradientPalettePtr);
CRGBPalette16 gCurrentPalette(CRGB::Black);
CRGBPalette16 gTargetPalette(gGradientPalettes[0]);