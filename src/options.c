#include "options.h"

static void logic(void);
static void draw(void);

static void createButton(char *str, int x, int y, void (*onClick)());
static void deinitOptions(void);
static void doButtons(void);
static void backButton(void);
static void drawButtons(void) ;

void initOption(void)
{
  app.delegate.logic = logic;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.buttonsTail = &stage.buttonsHead;

  createButton("<", 16, 540, NULL);
}

static void logic(void)
{
  doButtons();
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
      if(app.clicked) {
        b->onClick();
      }
    } else {
      b->isHover = 0;
    }

    prev = b;
  }
}

static void backButton(void) 
{
  deinitOptions();
  initMenu();
}

static void draw(void)
{
  drawText(FNT_HEAD, 127, 94, "OPTIONS");

  drawButtons();
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
  button->onClick = backButton;
  button->next = NULL;

  stage.buttonsTail->next = button;
  stage.buttonsTail = button;
}

static void deinitOptions(void)
{
  Button *b;	
  while (stage.buttonsHead.next)
  {
    b = stage.buttonsHead.next;
    stage.buttonsHead.next = b->next;
    if (b->normal != NULL) {
      SDL_DestroyTexture(b->normal);
    }
    if (b->hover != NULL) {
      SDL_DestroyTexture(b->hover);
    }
    free(b);
  }
}