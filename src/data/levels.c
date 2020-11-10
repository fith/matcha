#include "levels.h"

//int w, h;
//int seed;
//int fox;
//SDL_Color colors[];

const int num_levels = 15;

const Level levels[] = {
        // Tutorial
        {.w = 4, .h = 1, .seed = 6, .fox = 0, .numColors = 2, .colors = NULL },
        {.w = 1, .h = 5, .seed = 4, .fox = 0, .numColors = 2, .colors = NULL },
        {.w = 4, .h = 4, .seed = 45, .fox = 0, .numColors = 3, .colors = NULL },
        {.w = 4, .h = 4, .seed = 822, .fox = 0, .numColors = 3, .colors = NULL },
        {.w = 4, .h = 4, .seed = 1822, .fox = 0, .numColors = 3, .colors = NULL },
        // 5
        {.w = 4, .h = 5, .seed = 1543, .fox = 0, .numColors = 3, .colors = NULL },
        {.w = 5, .h = 4, .seed = 2, .fox = 0, .numColors = 3, .colors = NULL },
        {.w = 5, .h = 5, .seed = 7, .fox = 0, .numColors = 3, .colors = NULL },
        {.w = 4, .h = 5, .seed = 9, .fox = 0, .numColors = 3, .colors = NULL },
        {.w = 5, .h = 4, .seed = 13, .fox = 0, .numColors = 3, .colors = NULL },
        // 10
        {.w = 5, .h = 6, .seed = 17, .fox = 0, .numColors = 4, .colors = NULL },
        {.w = 6, .h = 6, .seed = 2344, .fox = 0, .numColors = 4, .colors = NULL },
        {.w = 5, .h = 7, .seed = 2365, .fox = 0, .numColors = 4, .colors = NULL },
        {.w = 7, .h = 6, .seed = 2365, .fox = 0, .numColors = 4, .colors = NULL },
        {.w = 7, .h = 7, .seed = 2365, .fox = 0, .numColors = 4, .colors = NULL }
};