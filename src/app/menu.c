#include "menu.h"

static void logic(void);
static void draw(void);
// logic
static void doButtons(void);
// draw
static void drawButtons(void);
static void drawDots(void);
// button
static void createButton(char *str, int x, int y, void (*onClick)());
static void buttonOptions(void);
static void buttonExit(void);
static void buttonStart(void);

static void deinitMenu(void);



enum Transitions {
  NONE,
  OPTIONS
};
static int transition;

static SDL_Texture *dotRedTexture;
static SDL_Texture *dotYellowTexture;
static SDL_Texture *dotGreenTexture;

void initMenu(void)
{
  app.delegate.logic = logic;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.buttonsTail = &stage.buttonsHead;

  if(dotRedTexture == NULL) {
    dotRedTexture = loadTexture("resources/gfx/dotRed.png");
  }
  if(dotYellowTexture == NULL) {
    dotYellowTexture = loadTexture("resources/gfx/dotYellow.png");
  }
  if(dotGreenTexture == NULL) {
    dotGreenTexture = loadTexture("resources/gfx/dotGreen.png");
  }

  transition = NONE;

  createButton("START", 345, 476, buttonStart);
  createButton("?", 16, 540, buttonOptions);
  createButton("X", 760, 8, buttonExit);
}

static void logic(void)
{
  doButtons();
}

static void buttonExit() {
  exit(0);
}

static void draw(void)
{
  drawTextCenter(FNT_HEAD, app.screenW/2, 94, "MATCHA");
  drawTextCenter(FNT_BODY, app.screenW/2, 228, "Hog & Sandwich");

  drawDots();

  drawButtons();
}

void doButtons() {
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

static void drawDots(void)
{
  blit(dotRedTexture, 288, 382);
  blit(dotYellowTexture, 368, 382);
  blit(dotGreenTexture, 448, 382);
}

void buttonOptions(void) {
  deinitMenu();
  initOptions();
}

void buttonStart(void) {
  deinitMenu();
  initLevel1();
}

static void createButton(char *str, int x, int y, void (*onClick)()) {
  Button *button = malloc(sizeof(Button));
  memset(button, 0, sizeof(Button));

  button->normal = textTexture(FNT_BUTT, str);
  button->hover = button->normal;
  button->isHover = 0;
  button->isClicked = 0;
  button->rect.x = x;
  button->rect.y = y;
  SDL_QueryTexture(button->normal, NULL, NULL, &button->rect.w, &button->rect.h);
  button->onClick = onClick;
  button->next = NULL;

  stage.buttonsTail->next = button;
  stage.buttonsTail = button;
}

static void deinitMenu(void)
{
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