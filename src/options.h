#include "common.h"

#define MAX_DUST 20

// draw.c
extern void blit(SDL_Texture *texture, int x, int y);
extern void blitFit(SDL_Texture *texture, SDL_Rect *dst);
extern SDL_Texture *loadTexture(char *filename);

// text.c
extern void drawText(int font, int x, int y, char *format, ...);
SDL_Texture* textTexture(int font, char *format, ...);

extern void initMenu(void);

extern Stage stage;
extern App app;