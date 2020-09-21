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

int main(int argc, char *argv[]) 
{
  long then;
  float remainder;

  memset(&app, 0, sizeof(App));
  app.options.enableFilm = 1;
  app.options.musicEnabled = 1;
  app.wins = 0;
  app.paused = 0;
  app.w = WINDOW_WIDTH;
  app.h = WINDOW_HEIGHT;

  atexit(cleanup);

  initSDL();

  dustTexture = loadTexture("gfx/dust.png");

  initSounds();

  initFonts();

  initMenu();

  then = SDL_GetTicks();
  remainder = 0;

  loadMusic("snd/humming.wav");
  if(app.options.musicEnabled == 1) {  
    playMusic(1);
  } 

  SDL_GetWindowSize(app.window,
                    &app.w,
                    &app.h);

  while (1)
  {
    prepareScene();

    doInput();

    app.delegate.logic();
    app.delegate.draw();

    if(app.options.enableFilm == 1) {
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
  if (dustTexture == NULL || !app.w || !app.h) {
    return;
  }
  static int offset = 0;
  if(++offset % 13 == 0) {
    int i;
    SDL_Rect rect;
    for (i = 0; i < MAX_DUST; i++)
    {
      rect.x = rand() % app.w;
      rect.y = rand() % app.h;
      rect.w = rect.h = 1 + rand() % 8;
      blitFit(dustTexture, &rect);
    }
    offset = 0;
  }
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}
