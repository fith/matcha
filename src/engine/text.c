#include "text.h"

static SDL_Texture *drawTextTexture;
static SDL_Surface *drawTextSurface;
static char drawTextBuffer[MAX_LINE_LENGTH];

SDL_Texture* textTexture(int font, char *format, ...);
void getTextSize(int font, int *w, int *h, char *format, ...);

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
      STBTTF_CloseFont(fonts[i].font);
      fonts[i].font = NULL;
    }
      fonts[i].font = STBTTF_OpenFont(app.renderer, "resources/fnt/abraxeousblack.ttf", (float)fonts[i].size);
    if(!fonts[i].font) {
      printf("STBTTF_OpenFont failed.");
      // handle error
    }
  }
}

void drawText(int font, int x, int y, char *format, ...) {
  va_list args;

  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

    STBTTF_RenderText(app.renderer, fonts[font].font, x, y, drawTextBuffer);
}

void getTextSize(int font, int *w, int *h, char *format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    *w = (int)STBTTF_MeasureText(fonts[font].font, drawTextBuffer);
    *h = fonts[font].font->baseline;
}

void drawTextRight(int font, int x, int y, char *format, ...) {
    int dx, dy;
    va_list args;
    int w, h;

    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    getTextSize(font, &w, &h, drawTextBuffer);

  dx = x - w;
  dy = y;
  
  drawText(font, dx, dy, drawTextBuffer);
}

void drawTextCenter(int font, int x, int y, char *format, ...) {
    int dx, dy;
    va_list args;
    int w,h;
  
  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

    getTextSize(font, &w, &h, drawTextBuffer);

  dx = x - (w/2);
  dy = y;
  
  drawText(font, dx, dy, drawTextBuffer);
}

SDL_Texture* textTexture(int font, char *format, ...)
{
  SDL_Texture* texture = NULL;
  int w, h;
  SDL_Color color = {
    fonts[font].r, 
    fonts[font].g, 
    fonts[font].b, 
    fonts[font].a
  };

  if (font < 0 || font > MAX_FONTS-1) {
    printf("Font out of range: %i\n", font);
  }

    if(!fonts[font].font) {
        printf("Failed to find font: %i", font);
        return NULL;
    }

  va_list args;
  va_start(args, format);
  vsprintf(drawTextBuffer, format, args);
  va_end(args);

    getTextSize(font, &w, &h, drawTextBuffer);

    texture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888,
                                               SDL_TEXTUREACCESS_TARGET, w, h);

    SDL_SetRenderTarget(app.renderer, texture);
    SDL_RenderClear(app.renderer);
    drawText(font, 0, 0, drawTextBuffer);
    //Detach the texture
    SDL_SetRenderTarget(app.renderer, NULL);
//  if(!(drawTextSurface = TTF_RenderText_Blended(fonts[font].font, drawTextBuffer, color))) {
//      //handle error here, perhaps print TTF_GetError at least
//      printf("Failed to render text (font: %i): %s", font, TTF_GetError());
//      exit(1);
//  } else {
//      //perhaps we can reuse it, but I assume not for simplicity.
//      texture = SDL_CreateTextureFromSurface(app.renderer, drawTextSurface);
//      SDL_FreeSurface(drawTextSurface);
//  }
  return texture;
}