#include "input.h"

static void handleWindowEvent(SDL_Event* e);

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

      case SDL_WINDOWEVENT:
        handleWindowEvent(&event);
        break;

      default:
        break;
    }
  }
}

static void handleWindowEvent(SDL_Event* e) {
  switch(e->window.event)
        {
            //Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_MAXIMIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            app.w = e->window.data1;
            app.h = e->window.data2;
            // SDL_RenderPresent( app.renderer );
            break;

            //Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
            // SDL_RenderPresent( app.renderer );
            break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
            case SDL_WINDOWEVENT_MINIMIZED:
            app.paused = 1;
            break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
            case SDL_WINDOWEVENT_RESTORED:
            app.paused = 0;
            break;
        }
}