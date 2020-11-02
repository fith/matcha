#include "text.h"

static SDL_Texture *drawTextTexture;
static SDL_Surface *drawTextSurface;
static char drawTextBuffer[MAX_LINE_LENGTH];

SDL_Texture* textTexture(int font, char *format, ...);

Font fonts[MAX_FONTS] = {
  {FNT_HEAD, 128, NULL, 255, 240, 220, 255}, 
  {FNT_BODY, 36, NULL, 255, 240, 220, 255}, 
  {FNT_BUTT, 36, NULL, 255, 240, 220, 255}
};

void initFonts(void)
{
  int i;
  for (i = 0; i < MAX_FONTS; i++) {
    if(fonts[i].font != NULL) {
      TTF_CloseFont(fonts[i].font);
      fonts[i].font = NULL;
    }
    fonts[i].font = TTF_OpenFont("resources/fnt/abraxeousblack.ttf", fonts[i].size);
    if(!fonts[i].font) {
      printf("TTF_OpenFont: %s\n", TTF_GetError());
      // handle error
    }
  }
}

void drawText(int font, int x, int y, char *format, ...) {
  va_list args;

  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

  drawTextTexture = textTexture(font, "%s", drawTextBuffer);
  blit(drawTextTexture, x, y);
  SDL_DestroyTexture(drawTextTexture);
}

void drawTextRight(int font, int x, int y, char *format, ...) {
  int w,h;
  int dx, dy;
  va_list args;
  
  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

  if(TTF_SizeText(fonts[font].font, drawTextBuffer, &w, &h)) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return;
  }

  dx = x - w;
  dy = y;
  
  drawText(font, dx, dy, drawTextBuffer);
}

void drawTextCenter(int font, int x, int y, char *format, ...) {
  int w,h;
  int dx, dy;
  va_list args;
  
  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

  if(TTF_SizeText(fonts[font].font, drawTextBuffer, &w, &h)) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return;
  }

  dx = x - (w/2);
  dy = y;
  
  drawText(font, dx, dy, drawTextBuffer);
}

SDL_Texture* textTexture(int font, char *format, ...)
{
  SDL_Texture* texture = NULL;
  SDL_Color color = {
    fonts[font].r, 
    fonts[font].g, 
    fonts[font].b, 
    fonts[font].a
  };

  if (font < 0 || font > MAX_FONTS-1) {
    printf("Font out of range: %i\n", font);
  }

  va_list args;
  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

  if(!fonts[font].font) {
    printf("Failed to find font: %i", font);
    return NULL;
  }
  if(!(drawTextSurface = TTF_RenderText_Blended(fonts[font].font, drawTextBuffer, color))) {
      //handle error here, perhaps print TTF_GetError at least
      printf("Failed to render text (font: %i): %s", font, TTF_GetError());
      exit(1);
  } else {
      //perhaps we can reuse it, but I assume not for simplicity.
      texture = SDL_CreateTextureFromSurface(app.renderer, drawTextSurface);
      SDL_FreeSurface(drawTextSurface);
  }
  return texture;
}