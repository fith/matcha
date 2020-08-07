#include "input.h"

void doKeyDown(SDL_KeyboardEvent *event) 
{
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

void doKeyUp(SDL_KeyboardEvent *event) 
{
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}

void doMouseUp(SDL_MouseButtonEvent *event) 
{
  if(event->clicks == 1) {
    app.clicked = 1;
  }
  app.mouseDown = 0;
  app.mouseUpEvent = event;
}

void doMouseDown(SDL_MouseButtonEvent *event) 
{
  app.mouseDown = 1;
  app.mouseDownEvent = event;
  app.mouseUpEvent = NULL;
}

int isMouseDown() {
  return (app.mouseDownEvent != NULL && app.mouseUpEvent == NULL) ? 1 : 0;
}

void doInput(void) {
  SDL_Event event;
  app.clicked = 0;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(0);
        break;

      case SDL_KEYDOWN:
        doKeyDown(&event.key);
        break;

      case SDL_KEYUP:
        doKeyUp(&event.key);
        break;
      
      case SDL_MOUSEBUTTONUP:
        doMouseUp(&event.button);
        break;

      case SDL_MOUSEBUTTONDOWN:
        doMouseDown(&event.button);
        break;

      default:
        break;
    }
  }
}


