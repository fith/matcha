// typedef struct Entity Entity;
typedef struct Dot Dot;
typedef struct Font Font;
typedef struct Button Button;
typedef struct AnimateMove AnimateMove;

typedef struct {
  void (*logic)(void);
  void (*draw)(void);
} Delegate;

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];
  SDL_MouseButtonEvent *mouseDownEvent;
  SDL_MouseButtonEvent *mouseUpEvent;
  int clicked;
  int mouseDown;
  int enableMusic;
  int enableFilm;
} App;

struct Dot {
  SDL_Texture *texture;
  SDL_Texture *icon;
  SDL_Color *color;
  float x;
  float y;
  int row;
  int col;
  int type;
  int health;
  AnimateMove *animateMove;
  Dot *goal;
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

struct Button {
  SDL_Texture *normal;
  SDL_Texture *hover;
  int isHover;
  int isClicked;
  int x, y, w, h;
  SDL_Rect *rect;
  void (*onClick)(void);
  Button *next;
};

typedef struct {
  Button buttonsHead, *buttonsTail;
  AnimateMove animateMoveHead, *animateMoveTail;
} Stage;

struct Font {
  int index;
  int size;
  TTF_Font *font;
  int r, g, b, a;
};