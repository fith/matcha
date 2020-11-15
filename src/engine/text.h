#ifndef _TEXT_H
#define _TEXT_H

#include "../shared/common.h"

// Engine
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTTF_IMPLEMENTATION
#include "../lib/stbttf.h"

struct Font {
    int index;
    int size;
    STBTTF_Font *font;
    int r, g, b, a;
};


// App

extern void blit(SDL_Texture *texture, int x, int y);
extern App app;

#endif