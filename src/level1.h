#include "common.h"

#include <tgmath.h>

// draw.c
extern void blit(SDL_Texture *texture, int x, int y);
extern void blitFit(SDL_Texture *texture, SDL_Rect *dst);
extern SDL_Texture *loadTexture(char *filename);
extern void drawLine(SDL_Texture *texture, int x1, int y1, int x2, int y2);
extern void drawSprite(Sprite* sprite);

// text.c
extern void drawText(int font, int x, int y, char *format, ...);
extern SDL_Texture* textTexture(int font, char *format, ...);

// util.c
extern float lerp(float v0, float v1, float t);

extern void initMenu(void);

extern Stage stage;
extern App app;