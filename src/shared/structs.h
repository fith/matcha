#ifndef STRUCTS_H
#define STRUCTS_H

#include "../lib/stb/stb_truetype.h"

// typedef struct Entity Entity;
typedef struct Dot Dot;
typedef struct Font Font;
typedef struct Button Button;
typedef struct UI UI;
typedef struct AnimateMove AnimateMove;
typedef struct Sprite Sprite;
typedef struct Board Board;
typedef struct Level Level;

typedef struct {
  void (*logic)(void);
  void (*draw)(void);
} Delegate;

typedef struct {
  int musicEnabled;
  float musicVolume;
  int soundEnabled;
  float soundVolume;
  int fullscreen;
  int enableFilm;
} Options;

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  Delegate delegate;
  Options options;
  int keyboard[MAX_KEYBOARD_KEYS];
  SDL_MouseButtonEvent *mouseDownEvent;
  SDL_MouseButtonEvent *mouseUpEvent;
  int clicked;
  int mouseDown;
  int wins;
  int level;
  int levelFarthest;
  int paused;
  int winW, winH;
  int screenW, screenH;
} App;

struct Level {
    int w, h;
    int seed;
    int fox;
    int numColors;
    SDL_Color *colors[GAME_COLORS];
};

//struct Board {
//  int w, h;
//  Dot *dots;
//};

struct Dot {
  SDL_Texture *texture;
  float rotation;
  int flip;
  Sprite *icon;
  SDL_Color *color;
  float x;
  float y;
  int row;
  int col;
  int type;
  int health;
  AnimateMove *animateMove;
  Dot *goal;
//  int falls;
};

struct AnimateMove {
  float startX;
  float startY;
  float endX;
  float endY;
  double startTime;
  float duration;
  float progress;
  AnimateMove *next;
};

// struct Transform {
//   float x, y;
//   float scale;
//   float rotation;
// };

// struct Animation {
//   Transform start;
//   Transform end;
//   double startTime;
//   float duration;
//   float progress;
//   Animation *next;
// }

// struct SpriteSheet {
//   SDL_Texture *texture;
//   int currentFrame;
//   int frameCount;
//   int frameDelay;
//   double startTime;
//   double lastFrameTime;
//   int loop;
// }

struct Sprite {
  SDL_Rect rect;
  float rotation;
  float scale;
  SDL_Color *color;
  SDL_Texture *texture;
  int currentFrame;
  int frameCount;
  int frameDelay;
  double startTime;
  double lastFrameTime;
  int blendMode;
  int flip;
  int loop;
};

struct Character {
  Sprite* idle;
  Sprite* active;
};

struct Button {
  SDL_Texture *normal;
  SDL_Texture *hover;
  int isHover;
  int isClicked;
  int outline;
  SDL_Rect rect;
  void (*onClick)(void);
  Button *next;
};

struct UI {
  SDL_Texture *texNormal;
  SDL_Texture *texHover;
  SDL_Texture *texActive;
  SDL_Color colNormal;
  SDL_Color colHover;
  SDL_Color colActive;
  int isHover;
  int isClicked;
  int isDragging;
  int isActive;
  SDL_Rect rect;
  void (*onClick)(void);
  void (*onDrag)(void);
};

typedef struct {
  Button buttonsHead, *buttonsTail;
  AnimateMove animateMoveHead, *animateMoveTail;
} Stage;



#endif
