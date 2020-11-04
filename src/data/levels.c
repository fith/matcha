#include "levels.h"

//int w, h;
//int seed;
//int fox;
//SDL_Color colors[];

#define NUM_LEVELS 11;

const Level levels[] = {
        {.w = 4, .h = 4, .seed = 1, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorOrange } },
        {.w = 4, .h = 4, .seed = 47, .fox = 0, .numColors = 3, .colors = { &colorBlue, &colorYellow, &colorGreen } },
        {.w = 4, .h = 4, .seed = 822, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorGreen } },
        {.w = 4, .h = 4, .seed = 1822, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorGreen } },
        {.w = 4, .h = 4, .seed = 322, .fox = 0, .numColors = 3, .colors = { &colorViolet, &colorIndigo, &colorBlue } },
        // 5
        {.w = 4, .h = 5, .seed = 1543, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorOrange } },
        {.w = 5, .h = 4, .seed = 2, .fox = 0, .numColors = 3, .colors = { &colorViolet, &colorYellow, &colorGreen } },
        {.w = 5, .h = 5, .seed = 7, .fox = 0, .numColors = 3, .colors = { &colorBlue, &colorOrange, &colorGreen } },
        {.w = 4, .h = 5, .seed = 9, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorIndigo } },
        {.w = 5, .h = 4, .seed = 13, .fox = 0, .numColors = 3, .colors = { &colorBlue, &colorYellow, &colorGreen } },
        // 10
        {.w = 7, .h = 7, .seed = 17, .fox = 0, .numColors = 4, .colors = { &colorBlue, &colorYellow, &colorGreen, &colorOrange } },
        {.w = 7, .h = 7, .seed = 17, .fox = 0, .numColors = 4, .colors = { &colorBlue, &colorYellow, &colorGreen, &colorOrange } }
};