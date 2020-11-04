#include "../shared/common.h"

// draw.c
extern void blit(SDL_Texture *texture, int x, int y);
extern void blitFit(SDL_Texture *texture, SDL_Rect *dst);
extern SDL_Texture *loadTexture(char *filename);

// text.c
extern void drawText(int font, int x, int y, char *format, ...);
extern void drawTextCenter(int font, int x, int y, char *format, ...);
extern SDL_Texture* textTexture(int font, char *format, ...);

extern void initOptions(void);
extern void initLevel1(int l);

extern Stage stage;
extern App app;

extern int num_levels;