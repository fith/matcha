#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PLAYER_SPEED 4
#define PLAYER_BULLET_SPEED 16

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS 2

#define SIDE_PLAYER 0
#define SIDE_ENEMY 1

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define FPS 60

#define ENEMY_BELLET_SPEED 8

#define MAX_STARS 500

#define MAX_SND_CHANNELS 8

// text
#define MAX_LINE_LENGTH 1024

#define MAX_FONTS 3

#define MAX_DUST 20

enum
{
    FNT_HEAD,
    FNT_BODY,
    FNT_BUTT
};

enum
{
    CH_ANY = -1,
    CH_PLAYER,
    CH_ENEMY_FIRE
};

enum
{
    SND_PLAYER_FIRE,
    SND_ENEMY_FIRE,
    SND_PLAYER_DIE,
    SND_ENEMY_DIE,
    SND_MAX
};