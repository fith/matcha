#include "draw.h"

void prepareScene(void) 
{
  int flicker = (rand() % 2) - 2;
  int r, g, b;
  r = g = b = 26 + flicker;
  SDL_SetRenderDrawColor(app.renderer, r, g, b, 255);
  SDL_RenderClear(app.renderer);
}

void presentScene(void) 
{
  SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
  SDL_Texture *texture;
  
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
  texture = IMG_LoadTexture(app.renderer, filename);

  if(!texture) {
    printf("Failed to load texture: %s\n", filename);
  }

  return texture;
}

SDL_Surface *loadSurface(char *filename)
{
  SDL_Surface *surface;
  
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
  surface = IMG_Load(filename);

  if(!surface) {
    printf("Failed to load texture: %s\n", filename);
  }

  return surface;
}

void blit(SDL_Texture *texture, int x, int y)
{
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitFit(SDL_Texture *texture, SDL_Rect *dst)
{
  SDL_RenderCopy(app.renderer, texture, NULL, dst);
}

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  dest.w = src->w;
  dest.h = src->h;

  SDL_RenderCopy(app.renderer, texture, src, &dest);
}

