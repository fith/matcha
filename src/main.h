#include "shared/common.h"

// init.c
extern void initSDL(void);
extern void cleanup(void);

// menu.c
extern void initMenu(void);

// draw.c
extern void prepareScene(void);
extern void presentScene(void);
extern void blitFit(SDL_Texture *texture, SDL_Rect *dst);
extern SDL_Texture *loadTexture(char *filename);

// input.c
extern void doInput(void);

// sound.c
extern void initSounds(void);
extern void loadMusic(char *filename);
extern void playMusic(int loop);

// text.c
extern void initFonts(void);

App app;
Stage stage;