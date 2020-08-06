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
static void drawDottedLine(int x1, int y1, int x2, int y2);

static SDL_Texture *dotTexture;
static SDL_Texture *dottedLineTexture;
static SDL_Texture *animalTexture;
static SDL_Texture *foodTexture;

// grid
static int startX, startY;

#define GRID_SIZE 7
#define TILE_SIZE 64
#define TILE_MARGIN 16
static Dot* grid[GRID_SIZE][GRID_SIZE] = { NULL };

#define MAX_COLORS 7
SDL_Color colorRed = {211, 44, 44}; // red
SDL_Color colorOrange = {211, 136, 44}; // orange
SDL_Color colorYellow = {229, 229, 26}; // yellow
SDL_Color colorGreen = {51, 204, 51}; // green
SDL_Color colorBlue = {44, 210, 211}; // blue
SDL_Color colorIndigo = {44, 90, 211}; // indigo
SDL_Color colorViolet = {183, 44, 211}; // violet
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

  startX = (WINDOW_WIDTH / 2) - (((GRID_SIZE * TILE_SIZE) + (16 * GRID_SIZE)) / 2);
  startY = (WINDOW_HEIGHT / 2) - (((GRID_SIZE * TILE_SIZE) + (16 * GRID_SIZE)) / 2);

  initDots();
}

static void drawGoals(void)
{
  Dot *d, *prev;
  for (d = stage.dotsHead.next; d != NULL; d = d->next) {
    if (d->goal != NULL) {
      drawDottedLine(d->x + TILE_SIZE/2.0, d->y + TILE_SIZE/2.0, d->goal->x + TILE_SIZE/2.0, d->goal->y + TILE_SIZE/2.0);
    }
  }
}

static void drawDottedLine(int x1, int y1, int x2, int y2) {
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
  srcRect.h = 12;

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
                    dottedLineTexture,
                    &srcRect,
                    &dstRect,
                    theta,
                    &center,
                    SDL_FLIP_NONE);
}

static void initDots()
{
  int x,y;
  Dot *d;
    
  // Food
  d = malloc(sizeof(Dot));
  memset(d, 0, sizeof(Dot));
  d->row = rand() % GRID_SIZE;
  d->col = rand() % GRID_SIZE;
  d->x = startX + d->row * TILE_SIZE + (d->row * TILE_MARGIN) + TILE_MARGIN;
  d->y = startY + d->col * TILE_SIZE + (d->col * TILE_MARGIN) + TILE_MARGIN;
  d->texture = foodTexture;
  d->color = colors[MAX_COLORS-1];
  d->locked = 0;
  grid[d->row][d->col] = d;
  stage.dotsTail->next = d;
  stage.dotsTail = d;

  // Animal
  d = NULL;
  d = malloc(sizeof(Dot));
  memset(d, 0, sizeof(Dot));
  do {
  x = rand() % GRID_SIZE;
  y = rand() % GRID_SIZE;
  } while (grid[x][y] != NULL);
  d->row = x;
  d->col = y;
  d->x = startX + d->row * TILE_SIZE + (d->row * TILE_MARGIN) + TILE_MARGIN;
  d->y = startY + d->col * TILE_SIZE + (d->col * TILE_MARGIN) + TILE_MARGIN;
  d->texture = animalTexture;
  d->color = colors[MAX_COLORS-1];
  d->locked = 0;
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
      d->x = startX + d->row * TILE_SIZE + (d->row * TILE_MARGIN) + TILE_MARGIN;
      d->y = startY + d->col * TILE_SIZE + (d->col * TILE_MARGIN) + TILE_MARGIN;
      d->texture = dotTexture;
      d->color = colors[rand() % (MAX_COLORS - 1)];
      d->locked = 0;
      grid[x][y] = d;
      stage.dotsTail->next = d;
      stage.dotsTail = d;
    }
  }
}

static void logic(void)
{
  doButtons();
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

void doButtons() {
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
      if(app.clicked) {
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
  int x,y;
  for(x = 0; x < GRID_SIZE; x++) {
    for(y = 0; y < GRID_SIZE; y++) {
      grid[x][y] = NULL;
    }
  }

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

  Dot *d;
  while (stage.dotsHead.next)
  {
    d = stage.dotsHead.next;
    stage.dotsHead.next = d->next;
    free(d);
  }
}