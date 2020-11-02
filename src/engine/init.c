#include "init.h"

static SDL_Surface *icon;
static SDL_Surface *cursorSurface;
static SDL_Cursor *cursor;

void initSDL(void)
{
  int renderFlags, windowFlags;

  renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

  windowFlags = SDL_WINDOW_RESIZABLE;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  app.window = SDL_CreateWindow("MATCHA", 
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

  if(!app.window) {
    printf("Failed to open %d x %x window: %s\n", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
    exit(1);
  }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, renderFlags);

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderSetLogicalSize(app.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  if(!app.renderer) {
    printf("Failed to create renderer: %s\n", SDL_GetError());
    exit(1);
  }

  IMG_Init(IMG_INIT_PNG);

  icon = loadSurface("resources/gfx/icon.png");
  SDL_SetWindowIcon(app.window, icon);

  cursorSurface = loadSurface("resources/gfx/mouse.png");
  cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
  if (!cursor) {
      printf("Failed to create cursor: %s\n", SDL_GetError());
      exit(1);
  }
  SDL_SetCursor(cursor);
  SDL_ShowCursor(1);

  if(TTF_Init()==-1) {
      printf("TTF_Init: %s\n", TTF_GetError());
      exit(2);
  }

  // open 44.1KHz, signed 16bit, system byte order,
  //      stereo audio, using 1024 byte chunks
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
  {
    printf("Couldn't initialize SDL Mixer.\n");
    exit(1);
  }

  Mix_AllocateChannels(MAX_SND_CHANNELS);
}

void cleanup(void) 
{
  if (cursor) {
    SDL_FreeCursor(cursor);
  }
  if (cursorSurface) {
    SDL_FreeSurface(cursorSurface);
  }
  if (icon) {
    SDL_FreeSurface(icon);
  }
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  TTF_Quit();
  SDL_Quit();
}