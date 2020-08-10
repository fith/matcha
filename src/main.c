#include "main.h"

static SDL_Texture *dustTexture;
static void drawDust(void);

static void capFrameRate(long *then, float *remainder) 
{
  long wait, frameTime;

  wait = 16 + *remainder;
  *remainder -= (int)*remainder;

  frameTime = SDL_GetTicks() - *then;

  wait -= frameTime;

  if (wait < 1)
  {
    wait = 1;
  }

  SDL_Delay(wait);

  *remainder += 0.667;

  *then = SDL_GetTicks();
}

int main() 
{
  long then;
  float remainder;

  memset(&app, 0, sizeof(App));
  app.enableFilm = 1;
  app.enableMusic = 1;

  atexit(cleanup);

  initSDL();

  dustTexture = loadTexture("gfx/dust.png");

  initSounds();

  initFonts();

  initMenu();

  then = SDL_GetTicks();
  remainder = 0;

  if(app.enableMusic == 1) {
    loadMusic("snd/humming.wav");
    playMusic(1);
  } 

  while (1)
  {
    prepareScene();

    doInput();

    app.delegate.logic();
    app.delegate.draw();

    if(app.enableFilm == 1) {
      drawDust();
    }

    presentScene();

    capFrameRate(&then, &remainder);
  }

  return 0;
}

static void drawDust(void)
{
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(dustTexture, SDL_BLENDMODE_ADD);
  if (dustTexture == NULL) {
    return;
  }
  static int offset = 0;
  if(++offset % 13 == 0) {
    int i;
    SDL_Rect rect;
    for (i = 0; i < MAX_DUST; i++)
    {
      rect.x = rand() % WINDOW_WIDTH;
      rect.y = rand() % WINDOW_HEIGHT;
      rect.w = rect.h = 1 + rand() % 8;
      blitFit(dustTexture, &rect);
    }
    offset = 0;
  }
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}
