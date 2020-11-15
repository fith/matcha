#include "level1.h"
#include <time.h>

// Init
void initLevel1(int l);
static void initDots(void);
static void logic(void);
static void draw(void);
static void deinitLevel1();
// Logic
static int isValidMove(Dot *from, Dot *to);
static int checkMatches(void);
static int checkMatchesRight(int x, int y);
static int checkMatchesDown(int x, int y);
static void doFalling(void);
static void doAnimal(void);
static void doDrag(void);
static void doAnimateMove(void);
static void removeDeadDots(void);
static void doButtons(void);
static void doGameOver(void);
// Drawing
static void drawButtons(void);
static void drawDots(void);
static void drawDot(Dot *dot);
static void drawGoals(void);
static void drawScore(void);
static void drawTime(void);
static void drawWin(void);
// Util
static void createButton(char *str, int x, int y, void (*onClick)());
static void backButton(void);
static void nextButton(void);
static void gridToScreen(int row, int col, float *x, float *y);
static void screenToGrid(float x, float y, int *row, int *col);
static void swapDots(int row1, int col1, int row2, int col2);
static void animateMoveTo(Dot *dot, float endX, float endY);
static void removeDot(int x, int y);
static Dot* createDot(int row, int col);
static SDL_Color* randomLevelColor();

static SDL_Texture *dotTexture;
static SDL_Texture *dottedLineTexture;
static SDL_Texture *animalTexture;
static SDL_Texture *foodTexture;

static Dot *dragging;
static int dragOffsetX, dragOffsetY;

// grid
#define TILE_SIZE 64
#define TILE_MARGIN 16
static Dot* grid[8][8];
static SDL_Rect gridRect;

static Level level;

static Dot *animal;
static Dot *food;
static Sprite *hogIdleSprite;
static Sprite *hogRunningSprite;
static Sprite *foodSprite;
static SDL_Texture *runningTexture;
static SDL_Texture *idleTexture;

int score;
int gameover;
Dot* lastMoveFrom;
Dot* lastMoveTo;

int animalColor;
int foodColor;

Uint32 startTime;
Uint32 currentTime;
Uint32 gameOverTime;

void initLevel1(int l)
{
    printf("LEVELS: %i", num_levels);
    if (l < num_levels) {
        level = levels[l];

        SDL_Color *c[GAME_COLORS];
        animalColor = rand() % DOT_COLORS;
        foodColor = rand() % DOT_COLORS;
        while (foodColor == animalColor) {
            foodColor = rand() % DOT_COLORS;
        }
        int j = 0;
        for (int i = 0; i < level.numColors; i++) {
            while(j == animalColor || j == foodColor) {
                j++;
            }
            c[i] = dotColors[j];
            j++;
        }
        memcpy(level.colors, c, sizeof c);

        srand(level.seed);

    } else {
        unsigned int seed = (unsigned int)time(NULL);
        srand(seed);
        SDL_Color *c[GAME_COLORS];
        int skip1 = rand() % DOT_COLORS;
        int skip2 = rand() % DOT_COLORS;
        while (skip2 == skip1) {
            skip2 = rand() % DOT_COLORS;
        }
        int j = 0;
        for (int i = 0; i < GAME_COLORS; i++) {
            while(j == skip1 || j == skip2) {
                j++;
            }
            c[i] = dotColors[j];
            j++;
        }

        level.w = 7;
            level.w = rand() % 2 + 6;
            level.h = rand() % 2 + 6;
            level.seed = seed;
            level.fox = 0;
            level.numColors = GAME_COLORS;
        memcpy(level.colors, c, sizeof c);

    }

    app.delegate.logic = logic;
    app.delegate.draw = draw;

  dragging = NULL;
  score = 0;
  gameover = 0;
  lastMoveFrom = NULL;
  lastMoveTo = NULL;
  startTime = SDL_GetTicks();
  currentTime = startTime;
  gameOverTime = 0;

  memset(&stage, 0, sizeof(Stage));
  stage.buttonsTail = &stage.buttonsHead;

//    Dot* (*A)[level.h] = ;
//    grid = malloc(sizeof(Dot*[level.w][level.h]));
//    for (int i = 0; i < level.w; i++) {
//        grid[i] = malloc(level.h * sizeof(grid[0]));
//    }


    if(dotTexture == NULL) {
    dotTexture = loadTexture("resources/gfx/dot.png");
  }
  if(dottedLineTexture == NULL) {
    dottedLineTexture = loadTexture("resources/gfx/dotted-line.png");
    SDL_SetTextureColorMod(dottedLineTexture, 255, 240, 220);
  }
  if(animalTexture == NULL) {
    animalTexture = loadTexture("resources/gfx/animal-hedgehog.png");
  }
  if(foodTexture == NULL) {
    foodTexture = loadTexture("resources/gfx/food-sandwich.png");
  }

  if(idleTexture == NULL) {
    idleTexture = loadTexture("resources/gfx/animal-hedgehog-idle-2.png");
  }
  if(runningTexture == NULL) {
    runningTexture = loadTexture("resources/gfx/animal-hedgehog-running-4.png");
  }
  
  if(!hogIdleSprite) {
    hogIdleSprite = malloc(sizeof(Sprite));
    memset(hogIdleSprite, 0, sizeof(Sprite));
    hogIdleSprite->rect.x = 0;
    hogIdleSprite->rect.y = 0;
    hogIdleSprite->rotation = 0.0;
    hogIdleSprite->scale = 1.0;
    hogIdleSprite->texture = idleTexture;
    SDL_QueryTexture(hogIdleSprite->texture, NULL, NULL, &hogIdleSprite->rect.w, &hogIdleSprite->rect.h);
    hogIdleSprite->currentFrame = 0;
    hogIdleSprite->frameCount = 2;
    hogIdleSprite->rect.w = hogIdleSprite->rect.w / hogIdleSprite->frameCount;
    hogIdleSprite->frameDelay = 500;
    hogIdleSprite->startTime = SDL_GetTicks();
    hogIdleSprite->lastFrameTime = hogIdleSprite->startTime;
    hogIdleSprite->blendMode = SDL_BLENDMODE_BLEND;
    hogIdleSprite->flip = 0;
    hogIdleSprite->loop = 1;
    hogIdleSprite->color = &colorWhite;
  }

    if(!hogRunningSprite) {
    hogRunningSprite = malloc(sizeof(Sprite));
    memset(hogRunningSprite, 0, sizeof(Sprite));
    hogRunningSprite->rect.x = 0;
    hogRunningSprite->rect.y = 0;
    hogRunningSprite->rotation = 0.0;
    hogRunningSprite->scale = 1.0;
    hogRunningSprite->texture = runningTexture;
    SDL_QueryTexture(hogRunningSprite->texture, NULL, NULL, &hogRunningSprite->rect.w, &hogRunningSprite->rect.h);
    hogRunningSprite->currentFrame = 0;
    hogRunningSprite->frameCount = 4;
    hogRunningSprite->rect.w = hogRunningSprite->rect.w / hogRunningSprite->frameCount;
    hogRunningSprite->frameDelay = 80;
    hogRunningSprite->startTime = SDL_GetTicks();
    hogRunningSprite->lastFrameTime = hogRunningSprite->startTime;
    hogRunningSprite->blendMode = SDL_BLENDMODE_BLEND;
    hogRunningSprite->flip = 0;
    hogRunningSprite->loop = 1;
    hogRunningSprite->color = &colorWhite;
  }

  if(!foodSprite) {
    foodSprite = malloc(sizeof(Sprite));
    memset(foodSprite, 0, sizeof(Sprite));
    foodSprite->rect.x = 0;
    foodSprite->rect.y = 0;
    foodSprite->rotation = 0.0;
    foodSprite->scale = 1.0;
    foodSprite->texture = foodTexture;
    SDL_QueryTexture(foodSprite->texture, NULL, NULL, &foodSprite->rect.w, &foodSprite->rect.h);
    foodSprite->currentFrame = 0;
    foodSprite->frameCount = 1;
    foodSprite->rect.w = foodSprite->rect.w / foodSprite->frameCount;
    foodSprite->frameDelay = 500;
    foodSprite->startTime = SDL_GetTicks();
    foodSprite->lastFrameTime = foodSprite->startTime;
    foodSprite->blendMode = SDL_BLENDMODE_BLEND;
    foodSprite->flip = 0;
    foodSprite->loop = 1;
    foodSprite->color = &colorWhite;
  }

  createButton("<", 16, 550, backButton);

  initDots();
}

static void drawGoals(void)
{
  for (int x = 0; x < level.w; x++) {
    for (int y = 0; y < level.h; y++) {
      if (grid[x][y] == NULL) {
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
  for (x = 0; x < level.w; x++) {
    for (y = (level.h-1); y > 0; y--) {
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
  for (x = 0; x < level.w; x++) {
    if (!grid[x][y]) {
      Dot *dot = createDot(x, y);
      int endY = dot->y;
      dot->y -= TILE_SIZE + TILE_MARGIN;
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

  if(app.mouseDown) {
    // button down
    if (inGrid && (grid[row][col] && !dragging)) {
      // pick it up
      dragging = grid[row][col];
      dragOffsetX = mouse.x - dragging->x;
      dragOffsetY = mouse.y - dragging->y;
      playSound(SND_DOT_LIFT, CH_ANY);
    }
  } else {
    // button is now up
    float x, y;
    if(dragging) {
      if(!inGrid) {
        // return home
        gridToScreen(dragging->row, dragging->col, &x, &y);
        animateMoveTo(dragging, x, y);
      } else {
        if(grid[row][col] && grid[row][col] != dragging && isValidMove(dragging, grid[row][col])) {
          lastMoveFrom = dragging;
          lastMoveTo = grid[row][col];
          swapDots(row, col, dragging->row, dragging->col);
        } else {
          // return home
          gridToScreen(dragging->row, dragging->col, &x, &y);
          animateMoveTo(dragging, x, y);
        }
      }
      dragging = NULL;
      playSound(SND_DOT_DROP, CH_ANY);
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
  if (grid[row1][col1]) {
    gridToScreen(row2, col2, &endX, &endY);
    animateMoveTo(grid[row1][col1], endX, endY);
  }
  // // dot 2
  if (grid[row2][col2]) {
    gridToScreen(row1, col1, &endX, &endY);
    animateMoveTo(grid[row2][col2], endX, endY);
  }

  // move 1 to temp
  Dot* dot = NULL;
  if (grid[row1][col1]) {
    dot = grid[row1][col1];
  }
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

  playSound(SND_DOT_SWAP, CH_ANY);
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
  am->duration = 180 + (rand() % 40);
  am->startTime = ticks;

  dot->animateMove = am;
}

static int isValidMove(Dot *from, Dot *to) {
  int frow, fcol;
  int trow, tcol;
  int dx, dy;

  frow = from->row;
  fcol = from->col;
  trow = to->row;
  tcol = to->col;

  dx = abs(frow - trow);
  dy = abs(fcol - tcol);

  // check that it's within range 1
  if (dx + dy > 1) {
    return 0;
  }

  // special rules for special dots
  //if (from == animal || from == food || to == animal || to == food) {
    // if they match color, they can swap
//    if (from->color == to->color) {
//        return 1;
//    } else {
//        return 0;
//    }
 // }

  return 1;
}

static void drawScore(void) {
  drawTextRight(FNT_BODY, app.screenW - 16, 0, "%6d", score);
}

static void drawTime(void) {
  Uint32 time = (SDL_GetTicks() - startTime) / 1000;
  int seconds = time % 60;
  int minutes = time / 60;
  // float seconds = time / 1000.0;
//  if (minutes < 1) {
//    drawTextRight(FNT_BODY, app.screenW - 16, 48, "%6d", seconds);
//  } else {
    drawTextRight(FNT_BODY, app.screenW - 16, 48, "%4d:%02d", minutes, seconds);
//  }
}

static void drawWin(void) {
  Uint32 seconds = 1 + (gameOverTime - startTime) / 1000;
  // int minutes = gameOverTime / 60;
  Uint32 hiscore = (score * score) / seconds ;
    drawTextCenter(FNT_HEAD, app.screenW/2, 72, "MATCHA");
  // drawTextCenter(FNT_BODY, app.w/2, 228, "Hog & Sandwich");
  drawTextCenter(FNT_BODY, app.screenW/2, 228, "Final Score: %d", hiscore);
}

static void checkWin(void) {
  int dx = abs(animal->row - food->row);
  int dy = abs(animal->col - food->col);

  if (dx + dy <= 1) {
    doGameOver();
  }
}

static void doGameOver(void) {
  if (gameover) {
    return;
  }

    createButton("Next", 688, 540, nextButton);
  gameover = 1;
  gameOverTime = SDL_GetTicks();
  app.wins++;
  app.level++;
    if (app.level > num_levels) {
        app.level = num_levels;
    }
    if (app.level > app.levelFarthest) {
        app.levelFarthest = app.level;
    }
}

static void initDots(void)
{
  int x,y;

  int startX = (app.screenW / 2) - (((level.w * TILE_SIZE) + (TILE_MARGIN * level.w)) / 2);
  int startY = (app.screenH / 2) - (((level.h * TILE_SIZE) + (TILE_MARGIN * level.h)) / 2);
  int width = ((TILE_SIZE + TILE_MARGIN) * level.w) + TILE_MARGIN;
  int height = ((TILE_SIZE + TILE_MARGIN) * level.h) + TILE_MARGIN;
  gridRect = (SDL_Rect){ startX, startY, width, height};

  int ax, ay, fx, fy;
  float distance;
  float minDistance = 3.0;
  float maxDistance = 4.0;
  do {
    ax = rand() % level.w;
    ay = rand() % level.h;
    fx = rand() % level.w;
    fy = rand() % level.h;
    distance = sqrt(pow(fx - ax, 2) + pow(fy - ay, 2) * 1.0);
  } while (distance < minDistance || distance > maxDistance);

  // set all the color dots
    for(x = 0; x < level.w; x++) {
        for(y = 0; y < level.h; y++) {
            grid[x][y] = createDot(x, y);
        }
    }

    // check matches so the game doesn't start with falling dots.
    int matches = checkMatches() ;
    printf("Matches: %d\n", matches);
    while(matches > 0) {
        for (int x = 0; x < level.w; x++) {
            for (int y = 0; y < level.h; y++) {
                if (grid[x][y]->health == 0) {
                    grid[x][y]->health = 1;
                    grid[x][y]->color = randomLevelColor();
                }
            }
        }
        matches = checkMatches();
        printf("Matches: %d\n", matches);
    }

  // Hog
  animal = grid[ax][ay];
  animal->icon = hogIdleSprite;
  animal->type = DOT_ANIMAL;

  // Animal
  food = grid[fx][fy];
  food->icon = foodSprite;
  food->type = DOT_FOOD;

  // Set Goal, this draws the line between them.
  animal->goal = food;
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
  d->color = randomLevelColor();
  d->animateMove = NULL;
  d->health = 1;
  d->type = DOT_DOT;
  d->flip = rand() % 4 - 1;
  d->rotation = rand() % 360;
  return d;
}

static SDL_Color* randomLevelColor() {
    return level.colors[rand() % level.numColors];
}

static void gridToScreen(int row, int col, float *x, float *y) {
  *x = gridRect.x + row * TILE_SIZE + (row * TILE_MARGIN) + TILE_MARGIN;
  *y = gridRect.y + col * TILE_SIZE + (col * TILE_MARGIN) + TILE_MARGIN;
}

static void screenToGrid(float x, float y, int *row, int *col) {
  int offsetX = x - gridRect.x; // the x inside the grid
  int offsetY = y - gridRect.y; // the x inside the grid
  if (offsetX < 0 || offsetX > gridRect.w) {
    return;
  }
  *row = offsetX / (TILE_SIZE + TILE_MARGIN);
  *col = offsetY / (TILE_SIZE + TILE_MARGIN);
}

static void logic(void)
{
  if(!gameover) {
      doDrag();
      checkMatches();
      removeDeadDots();
      doFalling();
  }
  doAnimateMove();
  // animate the animal's sprite.
  doAnimal();

  if (checkMatches() == 0) {
    checkWin();
  }
  doButtons();
}

static void draw(void)
{
  if (!gameover) {
    drawGoals();
    drawDots();
    drawScore();
    drawTime();
  }
  drawButtons();

  if (gameover) {
    drawDot(animal);
    drawDot(food);
    drawWin();
  }
}

static void updateTime() {
  currentTime = SDL_GetTicks();
}

static void backButton(void)
{
  deinitLevel1();
  initMenu();
}

static void nextButton(void) {
    deinitLevel1();
    initLevel1(app.level);
}

static void doAnimal(void) {
  int running = 0;
  int x = animal->row;
  int y = animal->col;
  int flip = 0;
  float rotation = 0.0;

  // check up
  if(y > 0 && grid[x][y-1] && grid[x][y-1]->color == animal->color) {
    running = 1;
    flip = 0;
    rotation = -90.0;
  }
  // check down
  if(y < (level.h - 1) && grid[x][y+1] && grid[x][y+1]->color == animal->color) {
    running = 1;
    flip = 0;
    rotation = 90.0;
  }
    // check left
    if(x > 0 && grid[x-1][y] && grid[x-1][y]->color == animal->color) {
        running = 1;
        flip = 1;
        rotation = 0.0f;
    }
    // check right
    if(x < (level.w - 1) && grid[x+1][y] && grid[x+1][y]->color == animal->color) {
        running = 1;
        flip = 0;
        rotation = 0.0f;
    }

  if (running || gameover) {
    animal->icon = hogRunningSprite;
  } else {
    animal->icon = hogIdleSprite;
  }

  if (gameover) {
      if (animal->x <= food->x) {
          flip = 0;
      } else {
          flip = 1;
      }
      rotation = 0.0;
      if (animal->y < food->y) {
          rotation = -90.0f;
          flip = 0;
      }
      if (animal->y < food->y) {
          rotation = 90.0f;
          flip = 0;
      }
  }

    animal->icon->rotation = rotation;
    animal->icon->flip = flip;
}

static void doAnimateMove(void) {
  double ticks = SDL_GetTicks();
  Dot *dot;
  AnimateMove *am;
  for (int x = 0; x < level.w; x++) {
    for (int y = 0; y < level.h; y++) {
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
    SDL_Rect rect = { b->rect.x, b->rect.y, b->rect.w, b->rect.h };
    if(SDL_PointInRect(&mouse, &rect) == SDL_TRUE) {
      b->isHover = 1;
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
  for (int x = 0; x < level.w; x++) {
    for (int y = 0; y < level.h; y++) {
      if (grid[x][y]) {
        drawDot(grid[x][y]);
      }
    }
  }
  // draw again, so always on top
  if (dragging) {
    drawDot(dragging);
  }
}

static void drawDot(Dot *dot) {
  // draw rect
  SDL_Rect dst;
  dst.x = dot->x;
  dst.y = dot->y;
  SDL_QueryTexture(dot->texture, NULL, NULL, &dst.w, &dst.h);

  // change scale if dragging
  if (dot == dragging) {
    float scale = 1.2;
    // calculate new x and y
    dst.x = (dst.x + dst.w/2) - (dst.w/2 * scale);
    dst.y = (dst.y + dst.h/2) - (dst.h/2 * scale);
    dst.w *= scale;
    dst.h *= scale;
  }

  // color and draw texture
  SDL_SetTextureColorMod(dot->texture, dot->color->r, dot->color->g, dot->color->b);
  blitFitRot(dot->texture, &dst, dot->flip, dot->rotation);

  // draw icon if needed
  if (dot->icon) {
    // if (dot->type == DOT_FOOD) {
    //   SDL_SetTextureColorMod(dot->icon, colorWhite.r, colorWhite.g, colorWhite.b);
    // } else if (dot->type == DOT_ANIMAL) {
    //   SDL_SetTextureColorMod(dot->icon, colorBlack.r, colorBlack.g, colorBlack.b);
    // }
    dot->icon->rect.x = dot->x;
    dot->icon->rect.y = dot->y;
    if (dot == dragging) {
        dot->icon->scale = 1.2;
    }
    drawSprite(dot->icon);
    dot->icon->scale = 1.0;
    // blitFit(dot->icon, &dst);
  }
}

static void drawButtons(void) {
  Button *b, *prev;
  for (b = stage.buttonsHead.next; b != NULL; b = b->next)
  {
    if(b->isHover == 1) {
      blit(b->hover, b->rect.x, b->rect.y);
      SDL_Rect rect = { b->rect.x-8, b->rect.y-4, b->rect.w+16, b->rect.h+8 };
      SDL_SetRenderDrawColor(app.renderer, 255, 240, 220, 255);
      SDL_RenderDrawRect(app.renderer, &rect);
    } else {
      blit(b->normal, b->rect.x, b->rect.y);
    }
  }
}

static int checkMatches() {
  int matches = 0;
  int x, y;
  for(x = 0; x < level.w; x++) {
    for(y = 0; y < level.h; y++) {
      matches += checkMatchesRight(x, y);
      matches += checkMatchesDown(x, y);
    }
  }
  return matches;
}

static int checkMatchesRight(int x, int y) {
  if (!grid[x][y]) {
    return 0;
  }
  int next = x;
  int matches = 1; // current dot matches itself.
  Dot *dots[(MATCH * 2)] = { NULL };
  dots[0] = grid[x][y];

  while (++next < level.w) {
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
    return 1;
  }

  return 0;
}

static int checkMatchesDown(int x, int y) {
  if (!grid[x][y]) {
    return 0;
  }
  int next = y;
  int matches = 1; // current dot matches itself.
  Dot *dots[(MATCH * 2) - 1] = { NULL };
  dots[0] = grid[x][y];

  while (++next < level.h) {
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
    return 1;
  }
  return 0;
}

static void removeDeadDots(void) {
  int total = 0;

  for (int x = 0; x < level.w; x++) {
    for (int y = 0; y < level.h; y++) {
      if (grid[x][y]) {
        if (grid[x][y]->health == 0) {
          total++;
          removeDot(x, y);
          int snd = rand() % 3;
          switch(snd) {
            case 0:
              playSound(SND_DOT_POP1, CH_ANY);
              break;
            case 1:
              playSound(SND_DOT_POP2, CH_ANY);
              break;
            case 2:
              playSound(SND_DOT_POP3, CH_ANY);
              break;
          }
        }
      }
    }
  }

  if (total == 0 && lastMoveFrom && lastMoveTo) {
    if (lastMoveFrom->type == DOT_DOT && lastMoveTo->type == DOT_DOT) {
      // they're both regular dots, move them back
      swapDots(lastMoveFrom->row, lastMoveFrom->col, lastMoveTo->row, lastMoveTo->col);
    } else if (lastMoveFrom->color != lastMoveTo->color) {
      // at least one is a special dot, but they don't match colors.
      swapDots(lastMoveFrom->row, lastMoveFrom->col, lastMoveTo->row, lastMoveTo->col);
    }
  }
  lastMoveFrom = NULL;
  lastMoveTo = NULL;

  score += SCORE_DOT * total;
}

static void removeDot(int x, int y) {
  Dot *dot = grid[x][y];
  grid[x][y] = NULL;
  if (dot->animateMove) {
    free(dot->animateMove);
  }
  dot->icon = NULL;
  free(dot);
}

static void createButton(char *str, int x, int y, void (*onClick)()) {
  Button *button = malloc(sizeof(Button));
  memset(button, 0, sizeof(Button));

  button->normal = textTexture(FNT_BUTT, str);
  button->hover = button->normal;
  button->isHover = 0;
  button->isClicked = 0;
  SDL_Rect rect = {x, y, 0, 0};
  SDL_QueryTexture(button->normal, NULL, NULL, &rect.w, &rect.h);
  button->rect = rect;
  button->onClick = onClick;
  button->next = NULL;

  stage.buttonsTail->next = button;
  stage.buttonsTail = button;
}

static void deinitLevel1(void) {
  // zero the grid
  food = NULL;
  animal = NULL;

  int x,y;
  for(x = 0; x < level.w; x++) {
    for(y = 0; y < level.h; y++) {
      if (grid[x][y]) {
        removeDot(x, y);
      }
      grid[x][y] = NULL;
    }
  }
//    for (int i = 0; i < level.w; i++) {
//        free(grid[i]);
//    }
//    free(grid);

  // state variables
  dragging = NULL;
  SDL_DestroyTexture(dotTexture);
  SDL_DestroyTexture(dottedLineTexture);
  SDL_DestroyTexture(animalTexture);
  SDL_DestroyTexture(foodTexture);
  SDL_DestroyTexture(runningTexture);
  SDL_DestroyTexture(idleTexture);
  dotTexture = NULL;
  dottedLineTexture = NULL;
  animalTexture = NULL;
  foodTexture = NULL;
  runningTexture = NULL;
  idleTexture = NULL;

  free(hogIdleSprite);
  hogIdleSprite = NULL;
  free(hogRunningSprite);
  hogRunningSprite = NULL;
  free(foodSprite);
  foodSprite = NULL;

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

