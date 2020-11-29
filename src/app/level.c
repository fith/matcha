#include "level.h"

static void gridToScreen(int row, int col, float *x, float *y);

// Game Board
Board* board;
Level level;
// Screen Grid
#define TILE_SIZE 64
#define TILE_MARGIN 16
static SDL_Rect gridRect;
// textures
SDL_Texture *dotTexture;

void draw() {
  float sx,sy;
  SDL_Rect dst;
  dst.w = TILE_SIZE;
  dst.h = TILE_SIZE;
  Piece *p;
  for (int x = 0; x < level.w; x++) {
    for (int y = 0; y < level.h; y++) {
      p = getCell(board, x, y);
      if (p) {
        gridToScreen(x, y, &sx, &sy);
        dst.x = sx;
        dst.y = sy;
        blitFit(dotTexture, &dst);
      }
    }
  }
}

void logic() {

}

void initLevel(int l) {
  printf("LEVELS: %i", num_levels);
  if (l < num_levels) {
    level = levels[l];
  }
  //GAME_COLORS

  app.delegate.logic = logic;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.buttonsTail = &stage.buttonsHead;

  board = createBoard(level.w, level.h, level.numColors);

  if(dotTexture == NULL) {
    dotTexture = loadTexture("resources/gfx/dot.png");
  }

  int startX = (app.screenW / 2) - (((level.w * TILE_SIZE) + (TILE_MARGIN * level.w)) / 2);
  int startY = (app.screenH / 2) - (((level.h * TILE_SIZE) + (TILE_MARGIN * level.h)) / 2);
  int width = ((TILE_SIZE + TILE_MARGIN) * level.w) + TILE_MARGIN;
  int height = ((TILE_SIZE + TILE_MARGIN) * level.h) + TILE_MARGIN;
  gridRect = (SDL_Rect){ startX, startY, width, height};
}

static void gridToScreen(int row, int col, float *x, float *y) {
  *x = gridRect.x + row * TILE_SIZE + (row * TILE_MARGIN) + TILE_MARGIN;
  *y = gridRect.y + col * TILE_SIZE + (col * TILE_MARGIN) + TILE_MARGIN;
}