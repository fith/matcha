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
static void doDrag(void);
static void doAnimateMove(void);
static void animateMoveTo(Dot *dot, float endX, float endY);
static int isValidMove(Dot *from, Dot *to);
static void checkMatches(void);
static void checkMatchesRight(int x, int y);
static void checkMatchesDown(int x, int y);
static void doFalling(void);
static void removeDot(Dot *dot);
static Dot* createDot(int row, int col);
static void removeDeadDots(void);

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
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      if (!grid[x][y]) {
        continue;
      }
      if (grid[x][y]->goal != NULL) {
        drawLine(dottedLineTexture, 
                  grid[x][y]->x + TILE_SIZE/2.0, 
                  grid[x][y]->y + TILE_SIZE/2.0, 
                  grid[x][y]->goal->x + TILE_SIZE/2.0, 
                  grid[x][y]->goal->y + TILE_SIZE/2.0);
      }
    }
  }
}

static void doFalling(void) {
  int x, y;
  for (x = (GRID_SIZE-1); x > 0; x--) {
    for (y = (GRID_SIZE-1); y > 0; y--) {
      if (!grid[x][y]) { // if this cell is empty
        if(grid[x][y-1]) { // check the above cell
          // move its contents down a space
          printf("This animate\n");
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
      printf("That animate\n");
      animateMoveTo(dot, dot->x, endY);
      grid[x][y] = dot;
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
    if (grid[row][col] && inGrid && !dragging) {
      // pick it up
      dragging = grid[row][col];
      dragOffsetX = mouse.x - dragging->x;
      dragOffsetY = mouse.y - dragging->y;
    }
  } else {
    // button is now up
    float x, y;
    if(dragging) {
      if(grid[row][col]) {
        if(inGrid == 1 && isValidMove(dragging, grid[row][col]) == 1 ) {
          // hit on a swappable dot
          swapDots(row, col, dragging->row, dragging->col);
        } else {
          gridToScreen(dragging->row, dragging->col, &x, &y);
          animateMoveTo(dragging, x, y);
        }
      } else {
        gridToScreen(dragging->row, dragging->col, &x, &y);
        animateMoveTo(dragging, x, y);
      }
      dragging = NULL;
    }
  }

  if (dragging) {
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
  if (grid[row1][col1]) {
    animateMoveTo(grid[row1][col1], endX, endY);
  }
  // // dot 2
  gridToScreen(row1, col1, &endX, &endY);
  if (grid[row2][col2]) {
    animateMoveTo(grid[row2][col2], endX, endY);
  }

  // move 1 to temp
  Dot* dot = grid[row1][col1];
  // move 2 to 1
  grid[row1][col1] = grid[row2][col2];
  if (grid[row1][col1]) {
    grid[row1][col1]->row = row1;
    grid[row1][col1]->col = col1;
  }
  // move temp to 2
  grid[row2][col2] = dot;
  if (grid[row2][col2]) {
    grid[row2][col2]->row = row2;
    grid[row2][col2]->col = col2;
  }
}

static void animateMoveTo(Dot *dot, float endX, float endY) {
  AnimateMove *am;
  double ticks = SDL_GetTicks();

  am = malloc(sizeof(AnimateMove));
  memset(am, 0, sizeof(AnimateMove));
  am->startX = dot->x;
  am->startY = dot->y;
  am->endX = endX;
  am->endY = endY;
  am->duration = 100;
  am->startTime = ticks;

  dot->animateMove = am;
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
  Dot *animal, *food;

  int startX = (WINDOW_WIDTH / 2) - (((GRID_SIZE * TILE_SIZE) + (TILE_MARGIN * GRID_SIZE)) / 2);
  int startY = (WINDOW_HEIGHT / 2) - (((GRID_SIZE * TILE_SIZE) + (TILE_MARGIN * GRID_SIZE)) / 2);
  int width = ((TILE_SIZE + TILE_MARGIN) * GRID_SIZE) + TILE_MARGIN;
  int height = ((TILE_SIZE + TILE_MARGIN) * GRID_SIZE) + TILE_MARGIN;
  gridRect = (SDL_Rect){ startX, startY, width, height};
    
  int ax, ay, fx, fy;
  float distance;
  float minDistance = 3.0;
  float maxDistance = 4.0;
  do {
    ax = rand() % GRID_SIZE;
    ay = rand() % GRID_SIZE;
    fx = rand() % GRID_SIZE;
    fy = rand() % GRID_SIZE;
    distance = sqrt(pow(fx - ax, 2) + pow(fy - ay, 2) * 1.0);
  } while (distance < minDistance || distance > maxDistance);

  // Food
  animal = malloc(sizeof(Dot));
  memset(animal, 0, sizeof(Dot));
  animal->row = ax;
  animal->col = ay;
  gridToScreen(animal->row, animal->col, &animal->x, &animal->y);
  animal->texture = dotTexture;
  animal->icon = animalTexture;
  animal->color = colors[rand() % MAX_COLORS];
  animal->animateMove = NULL;
  animal->type = DOT_ANIMAL;
  animal->health = 1;
  grid[animal->row][animal->col] = animal;

  // Animal
  food = malloc(sizeof(Dot));
  memset(food, 0, sizeof(Dot));
  food->row = fx;
  food->col = fy;
  gridToScreen(food->row, food->col, &food->x, &food->y);
  food->texture = dotTexture;
  food->icon = foodTexture;
  food->color = colors[rand() % MAX_COLORS];
  food->animateMove = NULL;
  food->type = DOT_FOOD;
  food->health = 1;
  grid[food->row][food->col] = food;

  animal->goal = food;

  for(x = 0; x < GRID_SIZE; x++) {
    for(y = 0; y < GRID_SIZE; y++) {
      if (!grid[x][y]) {
        grid[x][y] = createDot(x, y);
      }
      
    }
  }
}

static Dot* createDot(int row, int col) {
  Dot *d;
  d = malloc(sizeof(Dot));
  memset(d, 0, sizeof(Dot));
  d->row = row;
  d->col = col;
  gridToScreen(d->row, d->col, &d->x, &d->y);
  d->texture = dotTexture;
  d->icon = NULL;
  d->color = colors[rand() % MAX_COLORS];
  d->animateMove = NULL;
  d->health = 1;
  d->type = DOT_DOT;
  return d;
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
  printf("DoButtons\n");
  doButtons();
  
  printf("checkMatches\n");
  checkMatches();

  removeDeadDots();

  printf("doFalling\n");
  doFalling();

  printf("doDrag\n");
  doDrag();

  printf("doAnimateMove\n");
  doAnimateMove();
}

static void draw(void)
{
  printf("drawGoals\n");
  drawGoals();
  
  printf("drawDots\n");
  drawDots();

  printf("drawButtons\n");
  drawButtons();
}

static void backButton(void)
{
  deinitLevel1();
  initMenu();
}

static void doAnimateMove(void) {
  double ticks = SDL_GetTicks();
  Dot *dot;
  AnimateMove *am;
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      if (!grid[x][y]) {
        continue;
      }
      if (!grid[x][y]->animateMove) {
        continue;
      }
      dot = grid[x][y];
      am = grid[x][y]->animateMove;
      double elapsed = ticks - am->startTime;
      am->progress = elapsed / am->duration;

      dot->x = lerp(am->startX, am->endX, am->progress);
      dot->y = lerp(am->startY, am->endY, am->progress);

      if (elapsed > am->duration) {
        dot->x = am->endX;
        dot->y = am->endY;
        dot->animateMove = NULL;
        free(am);
      }
      
    }
  }
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
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      if (!grid[x][y]) {
        continue;
      }
      SDL_SetTextureColorMod(grid[x][y]->texture, grid[x][y]->color->r, grid[x][y]->color->g, grid[x][y]->color->b);
      blit(grid[x][y]->texture, grid[x][y]->x, grid[x][y]->y);
      if (grid[x][y]->icon) {
        if (grid[x][y]->type == DOT_FOOD) {
          SDL_SetTextureColorMod(grid[x][y]->icon, colorWhite.r, colorWhite.g, colorWhite.b);
        } else if (grid[x][y]->type == DOT_ANIMAL) {
          SDL_SetTextureColorMod(grid[x][y]->icon, colorBlack.r, colorBlack.g, colorBlack.b);
        }
        blit(grid[x][y]->icon, grid[x][y]->x, grid[x][y]->y);
      }
    }
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
      checkMatchesRight(x, y);
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
        if (dots[i]->type == DOT_DOT){
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

static void removeDeadDots(void) {
  for (int x = 0; x < GRID_SIZE; x++) {
    for (int y = 0; y < GRID_SIZE; y++) {
      if (grid[x][y]) {
        if (grid[x][y]->health == 0) {
          removeDot(grid[x][y]);
        }
      }
    }
  }
}

static void removeDot(Dot *dot) {
  if(dot) {
    grid[dot->row][dot->col] = NULL;
    dot->texture = NULL;
    dot->color = NULL;
    if (dot->animateMove) {
      free(dot->animateMove);
    }
    free(dot);
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
  // zero the grid
  int x,y;
  for(x = 0; x < GRID_SIZE; x++) {
    for(y = 0; y < GRID_SIZE; y++) {
      removeDot(grid[x][y]);
    }
  }

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
}

