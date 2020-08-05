typedef struct Entity Entity;
typedef struct Button Button;
typedef struct Explosion Explosion;
typedef struct Debris Debris;

typedef struct {
  void (*logic)(void);
  void (*draw)(void);
} Delegate;

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];
  int clicked;
  int enableMusic;
  int enableFilm;
} App;

struct Entity {
  float x;
  float y;
  int w;
  int h;
  SDL_Texture *texture;
  Entity *next;
  int color;
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
} Stage;



typedef struct {
  int index;
  int size;
  TTF_Font *font;
  int r, g, b, a;
} Font;