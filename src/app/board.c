#include "board.h"
Board* createBoard(int w, int h, int colors);
int matchStep(Board* board, int x, int y, int xStep, int yStep);
Piece* getCell(Board* board, int x, int y);
static Piece* pieceFactory(int color, int type);
void swapCells(Board *board, int x1, int y1, int x2, int y2);
// checks if a single move will be valid before it happens
int isValidMove(Board *board, x1, y1, x2, y2);
// checks if any valid moves exists (moves yet to be made)
int anyValidMove(Board *board);
// checks if any color matches exist now
int checkAnyMatches(Board *board, int numMatches);
int checkSingleMatches(Board *board, int x, int y, int numMatches);
int checkSingleSpecialMatches(Board *board, int x, int y);

Board* createBoard(int w, int h, int ncolors) {
    int size = w * h;
    int color;
    int type;
    struct Board *board = malloc( sizeof(*board) + sizeof(Piece* [size]) );

    if (ncolors > MAX_COLORS) {
        ncolors = MAX_COLORS;
    }

    for (int i = 0; i < size; i++) {
        color = rand() % ncolors;
        board->pieces[i] = pieceFactory(color, P_NONE);
    }

    return &board;
}

int isValidMove(Board *board, x1, y1, x2, y2) {
    int valid = 0;
    // test swap
    swapCells(board, x1, y1, x2, y2);
    if (checkSingleMatches(board, x1, y1, MATCH)) {
        valid = 1;
    } else if (checkSingleMatches(board, x2, y2, MATCH)) {
        valid = 1;
    } else if (checkSingleSpecialMatches(board, x1, y1)) {
        valid = 1;
    } else if (checkSingleSpecialMatches(board, x2, y2)) {
        valid = 1;
    }
    // undo test swap
    swapCells(board, x2, y2, x1, y1);
    return valid;
}

int anyValidMove(Board *board) {
    // returns true if there is still a valid move
    int x, y;

    // test all horizontal swaps
    for (x = 0; x < board->w -1; x++) {
        for(y = 0; y < board->h; y++) {
            swapCells(board, x, y, x+1, y);
            if (checkAnyMatches(board, MATCH)) {
                return 1;
            } else {
                swapCells(board, x+1, y, x, y);
            }
        }
    }

    // test all vertical swaps
    for (x = 0; x < board->w; x++) {
        for(y = 0; y < board->h - 1; y++) {
            swapCells(board, x, y, x, y + 1);
            if (checkAnyMatches(board, MATCH)) {
                return 1;
            } else {
                swapCells(board, x, y + 1, x, y);
            }
        }
    }

    // no valid move found
    return 0;
}

int checkSingleSpecialMatches(Board *board, int x, int y) {
    Piece *pieceA, *pieceB;

    // special matches require a goalType.
    if (!pieceA->goalType) {
        return 0;
    }

    pieceA = getCell(board, x, y);
    // right
    if (x < board->w - 1) {
        pieceB = getCell(board, x + 1, y);
        if (pieceB->type == pieceA->goalType) {
            return 1;
        }
    }
    // left
    if (x > 0) {
        pieceB = getCell(board, x - 1, y);
        if (pieceB->type == pieceA->goalType) {
            return 1;
        }
    }
    // below
    if (y < board->h - 1) {
        pieceB = getCell(board, x, y + 1);
        if (pieceB->type == pieceA->goalType) {
            return 1;
        }
    }
    // above
    if (y > 0) {
        pieceB = getCell(board, x, y - 1);
        if (pieceB->type == pieceA->goalType) {
            return 1;
        }
    }

    return 0;
}

int checkSingleMatches(Board *board, int x, int y, int numMatches) {
    // returns true if there are numMatches or more of the same symbol in a row or column
    int i, consecutive;
    Piece *pieceA, *pieceB;
    // check rows
    consecutive = 0;
    for (i = x; i < (board->w - 1); i++) {
        pieceA = getCell(board, i, y);
        pieceB = getCell(board, i + 1, y);
        if (pieceA->color == pieceB->color) {
            consecutive++;
        } else {
            consecutive = 0;
        }
        if (consecutive > numMatches) {
            return 1;
        }
    }

    // check columns
    consecutive = 0;
    for (i = y; i < (board->h - 1); i++) {
        pieceA = getCell(board, x, i);
        pieceB = getCell(board, x, i + 1);
        if (pieceA->color == pieceB->color) {
            consecutive++;
        } else {
            consecutive = 0;
        }
        if (consecutive > numMatches) {
            return 1;
        }
    }
}

void swapCells(Board *board, int x1, int y1, int x2, int y2) {
    Piece *pieceA, *pieceB;
    pieceA = getCell(board, x1, y1);
    pieceB = getCell(board, x2, y2);
    board->pieces[x1 + (y1 * board->w)] = pieceB;
    board->pieces[x2 + (y2 * board->w)] = pieceA;
}

int checkAnyMatches(Board *board, int numMatches) {
    // returns true if there are numMatches or more of the same symbol in a row or column
    int x, y, consecutive;
    Piece *pieceA, *pieceB;
    // check rows
    for (y = 0; y < board->h; y++) {
        consecutive = 0;
        for (x = 0; x < (board->w - 1); x++) {
            pieceA = getCell(board, x, y);
            pieceB = getCell(board, x + 1, y);
            if (pieceA->color == pieceB->color) {
                consecutive++;
            } else {
                consecutive = 0;
            }
            if (consecutive > numMatches) {
                return 1;
            }
        }
    }

    // check columns
    for (x = 0; x < board->w; x++) {
        consecutive = 0;
        for (y = 0; y < (board->h - 1); y++) {
            pieceA = getCell(board, x, y);
            pieceB = getCell(board, x, y + 1);
            if (pieceA->color == pieceB->color) {
                consecutive++;
            } else {
                consecutive = 0;
            }
            if (consecutive > numMatches) {
                return 1;
            }
        }
    }
}

static Piece* pieceFactory(int color, int type) {
    Piece p = {
        .color = color,
        .type = type
    };
    return &p;
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

  if (this->color == that->color) {
    // count the match and then check for the next match, recursively
    matches++;
    matches += matchStep(board, xNext, yNext, xStep, yStep);
  }

  return matches;
}

void destroyBoard(Board &board) {

}

Piece* getCell(Board *board, int x, int y) {
  return board->pieces[x + (y * board->w)];
}
