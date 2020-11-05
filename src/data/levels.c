#include "levels.h"

//int w, h;
//int seed;
//int fox;
//SDL_Color colors[];

const int num_levels = 15;

const Level levels[] = {
        // Tutorial
        {.w = 4, .h = 1, .seed = 2, .fox = 0, .numColors = 2, .colors = NULL },
        {.w = 1, .h = 5, .seed = 3, .fox = 0, .numColors = 2, .colors = { &colorGreen, &colorYellow } },
        {.w = 4, .h = 4, .seed = 45, .fox = 0, .numColors = 3, .colors = { &colorOrange, &colorYellow, &colorGreen } },
        {.w = 4, .h = 4, .seed = 822, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorGreen } },
        {.w = 4, .h = 4, .seed = 1822, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorGreen } },
        // 5
        {.w = 4, .h = 5, .seed = 1543, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorOrange } },
        {.w = 5, .h = 4, .seed = 2, .fox = 0, .numColors = 3, .colors = { &colorViolet, &colorYellow, &colorGreen } },
        {.w = 5, .h = 5, .seed = 7, .fox = 0, .numColors = 3, .colors = { &colorBlue, &colorOrange, &colorGreen } },
        {.w = 4, .h = 5, .seed = 9, .fox = 0, .numColors = 3, .colors = { &colorRed, &colorYellow, &colorIndigo } },
        {.w = 5, .h = 4, .seed = 13, .fox = 0, .numColors = 3, .colors = { &colorBlue, &colorYellow, &colorGreen } },
        // 10
        {.w = 5, .h = 6, .seed = 17, .fox = 0, .numColors = 4, .colors = { &colorBlue, &colorYellow, &colorGreen, &colorOrange } },
        {.w = 6, .h = 6, .seed = 2344, .fox = 0, .numColors = 4, .colors = { &colorBlue, &colorViolet, &colorIndigo, &colorGreen } },
        {.w = 5, .h = 7, .seed = 2365, .fox = 0, .numColors = 4, .colors = { &colorBlue, &colorViolet, &colorIndigo, &colorGreen } },
        {.w = 7, .h = 6, .seed = 2365, .fox = 0, .numColors = 4, .colors = { &colorYellow, &colorViolet, &colorOrange, &colorGreen } },
        {.w = 7, .h = 7, .seed = 2365, .fox = 0, .numColors = 4, .colors = { &colorYellow, &colorViolet, &colorOrange, &colorGreen } }
};