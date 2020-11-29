#ifndef LEVEL1_H
#define LEVEL1_H

#include "../shared/common.h"
#include <tgmath.h>

// draw.c
//extern void blit(SDL_Texture *texture, int x, int y);
extern void blitFit(SDL_Texture *texture, SDL_Rect *dst);
//extern void blitFitRot(SDL_Texture *texture, SDL_Rect *dst, int flip, float rotation);
extern SDL_Texture *loadTexture(char *filename);
//extern void drawLine(SDL_Texture *texture, int x1, int y1, int x2, int y2);
//extern void drawSprite(Sprite* sprite);
//
//// text.c
//extern void drawText(int font, int x, int y, char *format, ...);
//extern void drawTextRight(int font, int x, int y, char *format, ...);
//extern void drawTextCenter(int font, int x, int y, char *format, ...) ;
//extern SDL_Texture* textTexture(int font, char *format, ...);
//
//// util.c
//extern float lerp(float v0, float v1, float t);
//
//// sound.c
//extern void playSound(int id, int channel);
//
//extern void initMenu(void);

// board.c
extern Board* createBoard(int w, int h, int ncolors);
Piece* getCell(Board *board, int x, int y);

extern Stage stage;
extern App app;
extern const Level levels[];
extern const int num_levels;

#endif