

#pragma once

#include "Imports.h"

int s_start_pos[5];
int s_time[5] = {random(30), random(30), random(30), random(30), random(30)};
int s_color[5];
int s_brightness[5];
int s_tick[5] = {0, 0, 0, 0, 0};
int s_scale[5];
void salut(int s_count)
{
    static uint32_t prevTime;
    // стартовая позиция
    if (s_time[s_count] < s_tick[s_count])
    {
        s_time[s_count] = random(80) + 20;
        s_tick[s_count] = 0;
        s_start_pos[s_count] = random(NUM_LEDS_STRIPE);
        s_color[s_count] = random(255);
        s_brightness[s_count] = 255 - random(100);
        s_scale[s_count] = random(25) + 1;
    }

    s_tick[s_count]++;
    s_brightness[s_count] = s_brightness[s_count] - (s_brightness[s_count] / 12);
    s_color[s_count] = s_color[s_count] + 1;
    FOR_i(1, s_scale[s_count])
    {
        if ((s_start_pos[s_count] + s_tick[s_count] + i) < NUM_LEDS_STRIPE)
        {
            stripe[s_start_pos[s_count] + s_tick[s_count] + i] = CHSV(s_color[s_count], 255, s_brightness[s_count]);
        }
        if ((s_start_pos[s_count] - s_tick[s_count] - i) > 0)
        {
            stripe[s_start_pos[s_count] - s_tick[s_count] - i] = CHSV(s_color[s_count], 255, s_brightness[s_count]);
        }
    }
}
