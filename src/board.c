#include "board.h"
Board* createBoard(int w, int h, int colors);
int matchStep(Board* board, int x, int y, int xStep, int yStep);
Dot* getCell(Board* board, int x, int y);


Board* createBoard(int w, int h, int colors) {

}



int matchStep(Board* board, int x, int y, int xStep, int yStep) {
  int matches = 0;
  int xNext = x + xStep;
  int yNext = y + yStep;
  Dot* this = getCell(board, x, y);
  Dot* that = getCell(board, xNext, yNext);

  // check bounds
  if (xNext >= board->w || xNext < 0 || yNext >= board->h || yNext < 0) {
    return matches;
  }

  if (this->color == this->color) {
    // count the match and then check for the next match, recursively
    matches++;
    matches += matchStep(board, xNext, yNext, xStep, yStep);
  }

  return matches;
}

static void fall(Board* board) {
  int x, y;
  int i;
  for (i = 0; i < board->w * board->h; i++) {
    if ((board->dots[i]) == NULL) {

    }
      if (!grid[x][y]) { // if this cell is empty
        if(grid[x][y-1]) { // check the above cell
          // move its contents down a space
          swapDots(x, y-1, x, y);
          // Dot *dot = grid[x][y-1];
          // float endX, endY;
          // gridToScreen(x, y, &endX, &endY);
          // grid[x][y] = dot;
          // animateMoveTo(grid[x][y], endX, endY);
          // grid[x][y-1] = NULL;
        }
      }
    }
  }

  // top row
  y = 0;
  for (x = 0; x < GRID_SIZE; x++) {
    if (!grid[x][y]) {
      Dot *dot = createDot(x, y);
      int endY = dot->y;
      dot->y -= TILE_SIZE + TILE_MARGIN;
      animateMoveTo(dot, dot->x, endY);
      grid[x][y] = dot;
    }
  }
}

void destroyBoard(Board &board) {

}

Dot* getCell(Board &board, int x, int y) {
  return board[x + (y * board->w)];
}
