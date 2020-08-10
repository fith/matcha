#include "level1.h"

static void logic(void);
static void draw(void);
static void createButton(char *str, int x, int y, void (*onClick)());
static void backButton(void);
static void deinitLevel1(void);
static void drawButtons(void);
static void doButtons(void);
static void initDots(void);
static void drawDots(void);
static void drawGoals(void);
static void gridToScreen(int row, int col, float *x, float *y);
static void screenToGrid(float x, float y, int *row, int *col);
static void swapDots(int row1, int col1, int row2, int col2);
static float lerp(float v0, float v1, float t);
static void doAnimateMove(void);
static void animateMoveTo(Dot *dot, float endX, float endY);
static int isValidMove(Dot *from, Dot *to);
static void checkMatches(void);
static void createMatch(Dot *dot);
static void doMatches(void);
static void checkMatchesRight(int x, int y);
static void checkMatchesDown(int x, int y);
static void removeDot(Dot *dot);
static int alreadyMatched(Dot *Dot);

static SDL_Texture *dotTexture;
static SDL_Texture *dottedLineTexture;
static SDL_Texture *animalTexture;
static SDL_Texture *foodTexture;

static Dot *dragging;
static int dragOffsetX, dragOffsetY;

// grid
#define GRID_SIZE 7
#define TILE_SIZE 64
#define TILE_MARGIN 16
static Dot* grid[GRID_SIZE][GRID_SIZE] = { NULL };
static SDL_Rect gridRect;

#define MAX_COLORS 7
static SDL_Color colorRed = {211, 44, 44}; // red
static SDL_Color colorOrange = {211, 136, 44}; // orange
static SDL_Color colorYellow = {229, 229, 26}; // yellow
static SDL_Color colorGreen = {51, 204, 51}; // green
static SDL_Color colorBlue = {44, 210, 211}; // blue
static SDL_Color colorIndigo = {44, 90, 211}; // indigo
static SDL_Color colorViolet = {183, 44, 211}; // violet
static SDL_Color colorWhite = {255, 240, 220}; // white
static SDL_Color colorBlack = {26, 26, 26}; // white
static SDL_Color *colors[] = {&colorRed,
                              &colorOrange,
                              &colorYellow,
                              &colorGreen,
                              &colorBlue,
                              &colorIndigo,
                              &colorViolet};

void initLevel1(void)
{
  app.delegate.logic = logic;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.buttonsTail = &stage.buttonsHead;
  stage.dotsTail = &stage.dotsHead;
  stage.animateMoveTail = &stage.animateMoveHead;

  if(dotTexture == NULL) {
    dotTexture = loadTexture("gfx/dot.png");
  }
  if(dottedLineTexture == NULL) {
    dottedLineTexture = loadTexture("gfx/dotted-line.png");
    SDL_SetTextureColorMod(dottedLineTexture, 255, 240, 220);
  }
  if(animalTexture == NULL) {
    animalTexture = loadTexture("gfx/animal-hedgehog.png");
  }
  if(foodTexture == NULL) {
    foodTexture = loadTexture("gfx/food-sandwich.png");
  }

  createButton("<", 16, 540, backButton);

  initDots();
}

static void drawGoals(void)
{
  Dot *d, *prev;
  for (d = stage.dotsHead.next; d != NULL; d = d->next) {
    if (d->goal != NULL) {
      drawLine(dottedLineTexture, d->x + TILE_SIZE/2.0, d->y + TILE_SIZE/2.0, d->goal->x + TILE_SIZE/2.0, d->goal->y + TILE_SIZE/2.0);
    }
  }
}

static void doDrag(void) {
  SDL_Point mouse;
  SDL_GetMouseState(&mouse.x, &mouse.y);
  int row, col;
  screenToGrid(mouse.x, mouse.y, &row, &col);
  int inGrid = (SDL_PointInRect(&mouse, &gridRect) == SDL_TRUE) ? 1 : 0;

  if(app.mouseDown == 1) {
    // button down
    if (inGrid == 1 && dragging == NULL && grid[row][col]->locked == 0) {
      // pick it up
      dragging = grid[row][col];
      dragging->locked = 1;
      dragOffsetX = mouse.x - dragging->x;
      dragOffsetY = mouse.y - dragging->y;
    }
  } else {
    // button is now up
    if(dragging != NULL) {
      if(inGrid == 1 && grid[row][col]->locked == 0 && isValidMove(dragging, grid[row][col]) == 1 ) {
        swapDots(row, col, dragging->row, dragging->col);
      } else {
        float x, y;
        gridToScreen(dragging->row, dragging->col, &x, &y);
        animateMoveTo(dragging, x, y);
        dragging->locked = 0;
      }
      dragging = NULL;
    }
  }

  if (dragging != NULL) {
    // track to mouse
    dragging->x = mouse.x - dragOffsetX;
    dragging->y = mouse.y - dragOffsetY;
  }
}

static void swapDots(int row1, int col1, int row2, int col2) {
  if (row1 == row2 && col1 == col2) {
    return;
  }
  // create animations
  float endX, endY;
  gridToScreen(row2, col2, &endX, &endY);
  animateMoveTo(grid[row1][col1], endX, endY);
  // // dot 2
  gridToScreen(row1, col1, &endX, &endY);
  animateMoveTo(grid[row2][col2], endX, endY);

  // move 1 to temp
  Dot* dot = grid[row1][col1];
  // move 2 to 1
  grid[row1][col1] = grid[row2][col2];
  grid[row1][col1]->row = row1;
  grid[row1][col1]->col = col1;
  // move temp to 2
  grid[row2][col2] = dot;
  grid[row2][col2]->row = row2;
  grid[row2][col2]->col = col2;
}

static void animateMoveTo(Dot *dot, float endX, float endY) {
  AnimateMove *am;
  double ticks = SDL_GetTicks();

  am = malloc(sizeof(AnimateMove));
  memset(am, 0, sizeof(AnimateMove));
  am->dot = dot;
  am->startX = dot->x;
  am->startY = dot->y;
  am->endX = endX;
  am->endY = endY;
  am->duration = 100;
  am->startTime = ticks;
  stage.animateMoveTail->next = am;
  stage.animateMoveTail = am;
}

static int isValidMove(Dot *from, Dot *to) {
  if (from->row == to->row) {
    return (abs(from->col - to->col) == 1) ? 1 : 0;
  }
  if (from->col == to->col) {
    return (abs(from->row - to->row) == 1) ? 1 : 0;
  }
  return 0;
}

static void initDots(void)
{
  int x,y;
  Dot *d;

  int startX = (WINDOW_WIDTH / 2) - (((GRID_SIZE * TILE_SIZE) + (TILE_MARGIN * GRID_SIZE)) / 2);
  int startY = (WINDOW_HEIGHT / 2) - (((GRID_SIZE * TILE_SIZE) + (TILE_MARGIN * GRID_SIZE)) / 2);
  int width = ((TILE_SIZE + TILE_MARGIN) * GRID_SIZE) + TILE_MARGIN;
  int height = ((TILE_SIZE + TILE_MARGIN) * GRID_SIZE) + TILE_MARGIN;
  gridRect = (SDL_Rect){ startX, startY, width, height};
    
  int x1, y1, x2, y2;
  float distance;
  float minDistance = 3.0;
  float maxDistance = 4.0;
  do {
    x1 = rand() % GRID_SIZE;
    y1 = rand() % GRID_SIZE;
    x2 = rand() % GRID_SIZE;
    y2 = rand() % GRID_SIZE;
    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
  } while (distance < minDistance || distance > maxDistance);

  // Food
  d = malloc(sizeof(Dot));
  memset(d, 0, sizeof(Dot));
  d->row = x1;
  d->col = y1;
  gridToScreen(d->row, d->col, &d->x, &d->y);
  d->texture = foodTexture;
  d->color = colors[COL_VIOLET];
  d->locked = 0;
  d->health = 1;
  d->type = DOT_ANIMAL;
  grid[d->row][d->col] = d;
  stage.dotsTail->next = d;
  stage.dotsTail = d;

  // Animal
  d = NULL;
  d = malloc(sizeof(Dot));
  memset(d, 0, sizeof(Dot));
  do {
  x = x2;
  y = y2;
  } while (grid[x][y] != NULL);
  d->row = x;
  d->col = y;
  gridToScreen(d->row, d->col, &d->x, &d->y);
  d->texture = animalTexture;
  d->color = colors[COL_VIOLET];
  d->locked = 0;
  d->health = 1;
  d->type = DOT_FOOD;
  d->goal = stage.dotsTail;
  grid[d->row][d->col] = d;
  stage.dotsTail->next = d;
  stage.dotsTail = d;

  for(x = 0; x < GRID_SIZE; x++) {
    for(y = 0; y < GRID_SIZE; y++) {
      if (grid[x][y] != NULL) {
        continue;
      }
      d = NULL;
      d = malloc(sizeof(Dot));
      memset(d, 0, sizeof(Dot));
      d->row = x;
      d->col = y;
      gridToScreen(d->row, d->col, &d->x, &d->y);
      d->texture = dotTexture;
      d->color = colors[rand() % MAX_COLORS];
      d->locked = 0;
      d->health = 1;
      d->type = DOT_DOT;
      grid[x][y] = d;
      stage.dotsTail->next = d;
      stage.dotsTail = d;
    }
  }
  d = NULL;
}

static void gridToScreen(int row, int col, float *x, float *y) {
  *x = gridRect.x + row * TILE_SIZE + (row * TILE_MARGIN) + TILE_MARGIN;
  *y = gridRect.y + col * TILE_SIZE + (col * TILE_MARGIN) + TILE_MARGIN;
}

static void screenToGrid(float x, float y, int *row, int *col) {
  int offsetX = x - gridRect.x; // the x inside the gride
  int offsetY = y - gridRect.y; // the x inside the gride
  if (offsetX < 0 || offsetX > gridRect.w) {
    return;
  }
  *row = offsetX / (TILE_SIZE + TILE_MARGIN);
  *col = offsetY / (TILE_SIZE + TILE_MARGIN);
}

static void logic(void)
{
  doButtons();

  checkMatches();

  doMatches();

  doDrag();

  doAnimateMove();
}

static void draw(void)
{
  drawGoals();
  
  drawDots();

  drawButtons();
}

static void backButton(void)
{
  deinitLevel1();
  initMenu();
}

static void doAnimateMove(void) {
  AnimateMove *am, *prev;

  prev = &stage.animateMoveHead;
  double ticks = SDL_GetTicks();

  for (am = stage.animateMoveHead.next; am != NULL; am = am->next)
  {
    if(!am->dot) {
      if (am == stage.animateMoveTail) {
        stage.animateMoveTail = prev;
      }
      prev->next = am->next;
      free(am);
      am = prev;
    }

    Dot *dot = am->dot;
    double elapsed = ticks - am->startTime;
    am->progress = elapsed / am->duration;

    dot->x = lerp(am->startX, am->endX, am->progress);
    dot->y = lerp(am->startY, am->endY, am->progress);

    if (elapsed > am->duration) {
      dot->x = am->endX;
      dot->y = am->endY;
      dot->locked = 0;
      
      if (am == stage.animateMoveTail) {
        stage.animateMoveTail = prev;
      }

      dot = NULL;
      prev->next = am->next;
      free(am);
      am = prev;
    }
    prev = am;
  }
}

static float lerp(float v0, float v1, float t) {
  return v0 + t * (v1 - v0);
}

static void doButtons() {
  Button *b, *prev;
  prev = &stage.buttonsHead;
  SDL_Point mouse;
  SDL_GetMouseState(&mouse.x, &mouse.y);
  for (b = stage.buttonsHead.next; b != NULL; b = b->next)
  {
    // check if button clicked
    SDL_Rect rect = { b->x, b->y, b->w, b->h };
    if(SDL_PointInRect(&mouse, &rect) == SDL_TRUE) {
      b->isHover = 1;
      printf("App clicked: %i\n", app.clicked);
      if(app.clicked == 1) {
        b->onClick();
        return;
      }
    } else {
      b->isHover = 0;
    }
    prev = b;

  }
}

static void drawDots(void) {
  Dot *d, *prev;
  for (d = stage.dotsHead.next; d != NULL; d = d->next)
  {
    if (!d) {
      continue;
    }
    SDL_SetTextureColorMod(d->texture, d->color->r, d->color->g, d->color->b);
    blit(d->texture, d->x, d->y);
  }
}

static void drawButtons(void) {
  Button *b, *prev;
  for (b = stage.buttonsHead.next; b != NULL; b = b->next)
  {
    if(b->isHover == 1) {
      blit(b->hover, b->x, b->y);
      SDL_Rect rect = { b->x-8, b->y-4, b->w+16, b->h+8 };
      SDL_SetRenderDrawColor(app.renderer, 255, 240, 220, 255);
      SDL_RenderDrawRect(app.renderer, &rect);
    } else {
      blit(b->normal, b->x, b->y);
    }
  }
}

static void checkMatches() {
  int x, y;
  for(x = 0; x < GRID_SIZE; x++) {
    for(y = 0; y < GRID_SIZE; y++) {
      checkMatchesRight( x, y);
      checkMatchesDown(x, y);
    }
  }
}

static void checkMatchesRight(int x, int y) {
  if (!grid[x][y]) {
    return;
  }
  int next = x;
  int matches = 1; // current dot matches itself.
  Dot* dots[(MATCH * 2)] = { NULL };
  dots[0] = grid[x][y];
  
  while (++next < GRID_SIZE) {
    if (grid[next][y] == NULL) {
      break;
    }
    if (grid[next][y]->color == grid[x][y]->color) {
      dots[matches] = grid[next][y];
      matches++;
    } else {
      break;
    }
  }

  if (matches >= MATCH) {
    for(int i = 0; i < (MATCH * 2) - 1; i++) {
      if (dots[i] != NULL) {
        if (dots[i]->goal == NULL){
          dots[i]->health = 0;
        }
      }
    }
  }
}

static void checkMatchesDown(int x, int y) {
  if (!grid[x][y]) {
    return;
  }
  int next = y;
  int matches = 1; // current dot matches itself.
  Dot *dots[(MATCH * 2) - 1] = { NULL };
  dots[0] = grid[x][y];
  
  while (++next < GRID_SIZE) {
    if (!grid[x][next]) {
      break;
    }
    if (grid[x][next]->color == grid[x][y]->color) {
      dots[matches] = grid[x][next];
      matches++;
    } else {
      break;
    }
  }

  if (matches >= MATCH) {
    for(int i = 0; i < (MATCH * 2) - 1; i++) {
      if (dots[i] != NULL) {
        if (dots[i]->type == DOT_DOT){
          dots[i]->health = 0;
        }
      }
    }
  }
}

static void doMatches() {
  Dot *d, *prev;
  for (d = stage.dotsHead.next; d != NULL; d = d->next)
  {
    if (d->health == 0) {
      removeDot(d);
    }
  }
}

static void removeDot(Dot *dot) {
    Dot *d, *prev;
    prev = &stage.dotsHead;
    for (d = stage.dotsHead.next; d != NULL; d = d->next) {
      if(d == dot) {
        if (d == stage.dotsTail) 
        {
          stage.dotsTail = prev;
        }
        prev->next = d->next;
        free(d);
        d = prev;
      }
      prev = d;
    }
}

static void createButton(char *str, int x, int y, void (*onClick)()) {
  Button *button = malloc(sizeof(Button));
  memset(button, 0, sizeof(Button));

  button->normal = textTexture(FNT_BUTT, str);
  button->hover = button->normal;
  button->isHover = 0;
  button->isClicked = 0;
  button->x = x;
  button->y = y;
  SDL_QueryTexture(button->normal, NULL, NULL, &button->w, &button->h);
  button->onClick = onClick;
  button->next = NULL;

  stage.buttonsTail->next = button;
  stage.buttonsTail = button;
}

static void deinitLevel1(void)
{
  // state variables
  dragging = NULL;
  SDL_DestroyTexture(dotTexture);
  SDL_DestroyTexture(dottedLineTexture);
  SDL_DestroyTexture(animalTexture);
  SDL_DestroyTexture(foodTexture);
  dotTexture = NULL;
  dottedLineTexture = NULL;
  animalTexture = NULL;
  foodTexture = NULL;

  // zero the grid
  int x,y;
  for(x = 0; x < GRID_SIZE; x++) {
    for(y = 0; y < GRID_SIZE; y++) {
      grid[x][y] = NULL;
    }
  }

  // buttons and their textures
  Button *b;	
  while (stage.buttonsHead.next)
  {
    b = stage.buttonsHead.next;
    stage.buttonsHead.next = b->next;
    if (b->normal != NULL) {
      SDL_DestroyTexture(b->normal);
      b->normal = NULL;
    }
    if (b->hover != NULL) {
      SDL_DestroyTexture(b->hover);
      b->hover = NULL;
    }
    free(b);
  }

  
  AnimateMove *a;	
  while (stage.animateMoveHead.next)
  {
    a = stage.animateMoveHead.next;
    stage.animateMoveHead.next = a->next;
    a->dot = NULL;
    free(a);
  }

  // dots and their textures
  Dot *d;
  while (stage.dotsHead.next)
  {
    d = stage.dotsHead.next;
    stage.dotsHead.next = d->next;
    d->texture = NULL;
    d->color = NULL;
    free(d);
  }
}

