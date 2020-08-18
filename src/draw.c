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

void drawSprite(Sprite* sprite) {
  // get time
  double time = SDL_GetTicks();
  double frameTime = time - sprite->lastFrameTime;
  
  // figure out current frame
  if (frameTime > sprite->frameDelay) {
    sprite->currentFrame = (sprite->currentFrame < sprite->frameCount-1) ? sprite->currentFrame+1 : 0;
    sprite->lastFrameTime = time;
    printf("Changed Frame: %i\n", sprite->currentFrame);
  }
  

  // create source rect for frame
  SDL_Rect srcRect;
  // figure out current frame rect
  srcRect.x = (sprite->rect.w * sprite->currentFrame);
  srcRect.y = 0; // only supporting single row animations for now
  srcRect.w = sprite->rect.w;
  srcRect.h = sprite->rect.h;

  // create draw rect
  SDL_Rect dst;
  dst.x = sprite->rect.x;
  dst.y = sprite->rect.y;
  dst.w = sprite->rect.w;
  dst.h = sprite->rect.h;  

  // scale draw rect
  dst.x = (dst.x + dst.w/2) - (dst.w/2 * sprite->scale);
  dst.y = (dst.y + dst.h/2) - (dst.h/2 * sprite->scale);
  dst.w *= sprite->scale;
  dst.h *= sprite->scale;

  // calc center
  SDL_Point center;
  center.x = srcRect.w/2.0;
  center.y = srcRect.h/2.0;

  // render cope
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderCopyEx(app.renderer,
                    sprite->texture,
                    &srcRect,
                    &dst,
                    sprite->rotation,
                    &center,
                    sprite->flip);
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

void drawLine(SDL_Texture *texture, int x1, int y1, int x2, int y2) {
  float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
  float dy = y2 - y1;
  float dx = x2 - x1;
  float theta = atan(dy/dx);
  theta *= 180/PI; // rads to degs
  if(x1 > x2) {
    theta += 180;
  }

  SDL_Rect srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = distance;
  SDL_QueryTexture(texture, NULL, NULL, NULL, &srcRect.h);

  SDL_Rect dstRect;
  dstRect.x = x1 - srcRect.h/2.0;
  dstRect.y = y1 - srcRect.h/2.0;
  dstRect.w = distance;
  dstRect.h = srcRect.h;

  SDL_Point center;
  center.x = srcRect.h/2.0;
  center.y = srcRect.h/2.0;
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderCopyEx(app.renderer,
                    texture,
                    &srcRect,
                    &dstRect,
                    theta,
                    &center,
                    SDL_FLIP_NONE);
}