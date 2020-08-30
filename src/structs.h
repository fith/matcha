// typedef struct Entity Entity;
typedef struct Dot Dot;
typedef struct Font Font;
typedef struct Button Button;
typedef struct AnimateMove AnimateMove;
typedef struct Sprite Sprite;
typedef struct Board Board;

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
  int wins;
  int paused;
  int w, h;
} App;

struct Board {
  int w, h;
  Dot *dots;
};

struct Dot {
  SDL_Texture *texture;
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
  int falls;
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