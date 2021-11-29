#include "levels.h"

//int w, h;
//int seed;
//int fox;
//SDL_Color colors[];

const int num_levels = 15;

const Level levels[] = {
        // Tutorial
        {.w = 4, .h = 1, .seed = 7, .numColors = 2, .par = 2, .colors = NULL},
        {.w = 1, .h = 5, .seed = 2, .numColors = 2, .par = 2, .colors = NULL},
        {.w = 4, .h = 4, .seed = 1, .numColors = 3, .par = 4, .colors = NULL},
        {.w = 4, .h = 4, .seed = 822, .numColors = 3, .par = 4, .colors = NULL},
        {.w = 4, .h = 4, .seed = 1822, .numColors = 3, .par = 2, .colors = NULL},
        // 5
        {.w = 4, .h = 4, .seed = 1543, .numColors = 3, .par = 2, .colors = NULL},
        {.w = 4, .h = 4, .seed = 2, .numColors = 3, .par = 2, .colors = NULL},
        {.w = 4, .h = 4, .seed = 7, .numColors = 3, .par = 2, .colors = NULL},
        {.w = 4, .h = 5, .seed = 9, .numColors = 3, .par = 2, .colors = NULL},
        {.w = 5, .h = 4, .seed = 13, .numColors = 3, .par = 2, .colors = NULL},
        // 10
        {.w = 5, .h = 5, .seed = 18, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 5, .h = 6, .seed = 2344, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 5, .h = 5, .seed = 2365, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 4, .h = 5, .seed = 2365, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 5, .h = 5, .seed = 2365, .numColors = 4, .par = 2, .colors = NULL},
        // 15
        {.w = 5, .h = 4, .seed = 18, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 4, .h = 6, .seed = 2344, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 5, .h = 5, .seed = 7, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 6, .h = 4, .seed = 2365, .numColors = 4, .par = 2, .colors = NULL},
        {.w = 4, .h = 5, .seed = 1234, .numColors = 4, .par = 2, .colors = NULL}
};