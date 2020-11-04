#ifndef DEFS_H
#define DEFS_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

#ifndef degToRad
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#endif

#ifndef radToDeg
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)
#endif

#define PI 3.14159265

#define FPS 60

#define ENEMY_BELLET_SPEED 8

#define MAX_STARS 500

#define MAX_SND_CHANNELS 8

// text
#define MAX_LINE_LENGTH 1024

#define MAX_FONTS 3

#define MAX_DUST 20

#define MATCH 3

#define SCORE_DOT 10

enum
{
    FNT_HEAD,
    FNT_BODY,
    FNT_BUTT
};

enum DotTypes {
    DOT_DOT,
    DOT_ANIMAL,
    DOT_FOOD
};

enum DotColors {
    COL_RED,
    COL_ORANGE,
    COL_YELLOW,
    COL_GREEN,
    COL_BLUE,
    COL_INDIGO,
    COL_VIOLET
};

enum
{
    CH_ANY = -1,
    CH_PLAYER,
    CH_ENEMY_FIRE
};

enum
{
    SND_DOT_LIFT,
    SND_DOT_SWAP,
    SND_DOT_DROP,
    SND_DOT_POP1,
    SND_DOT_POP2,
    SND_DOT_POP3,
    SND_MAX
};


#endif