#ifndef _DEFS_H
#define _DEFS_H

// graphics
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_DUST 20

// game settings
#define DOT_COLORS 9
#define GAME_COLORS 5
#define MATCH 3
#define SCORE_DOT 10
enum DotTypes {
    DOT_DOT,
    DOT_ANIMAL,
    DOT_FOOD
};

// text
#define MAX_LINE_LENGTH 1024
#define MAX_FONTS 3
enum {
    FNT_HEAD,
    FNT_BODY,
    FNT_BUTT
};

// sound
#define MAX_SND_CHANNELS 8

enum {
    CH_ANY = -1,
    CH_PLAYER,
    CH_ENEMY_FIRE
};

enum {
    SND_DOT_LIFT,
    SND_DOT_SWAP,
    SND_DOT_DROP,
    SND_DOT_POP1,
    SND_DOT_POP2,
    SND_DOT_POP3,
    SND_MAX
};

// input
#define MAX_KEYBOARD_KEYS 350

// generic math
#define PI 3.14159265

#ifndef MAX
#define MAX(a, b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef degToRad
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#endif

#ifndef radToDeg
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)
#endif

#endif