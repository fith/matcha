#include "colors.h"

SDL_Color colorRed = {211, 44, 44}; // red
SDL_Color colorOrange = {211, 136, 44}; // orange
SDL_Color colorYellow = {229, 229, 26}; // yellow
SDL_Color colorGreen = {51, 204, 51}; // green
SDL_Color colorBlue = {44, 210, 211}; // blue
SDL_Color colorIndigo = {44, 90, 211}; // indigo
SDL_Color colorViolet = {183, 44, 211}; // violet
SDL_Color colorWhite = {255, 240, 220}; // white
SDL_Color colorBlack = {26, 26, 26}; // white

SDL_Color *dotColors[DOT_COLORS] = {
        &colorRed,
        &colorOrange,
        &colorYellow,
        &colorGreen,
        &colorBlue,
        &colorIndigo,
        &colorViolet
};