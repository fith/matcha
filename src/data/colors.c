#include "colors.h"

SDL_Color colorRed = {215, 66, 92}; // red *
SDL_Color colorOrange = {240, 134, 45}; // orange
SDL_Color colorYellow = {240, 232, 120}; // yellow *
SDL_Color colorGreen = {16, 168, 128}; // green *
SDL_Color colorBlue = {81, 161, 214}; // blue *
SDL_Color colorIndigo = {105, 88, 159}; // indigo
SDL_Color colorViolet = {68, 18, 58}; // violet *
SDL_Color colorWhite = {232, 227, 214}; // white
SDL_Color colorBlack = {26, 26, 26}; // white
SDL_Color colorPeach = { 251, 180, 146};
SDL_Color colorGrey = { 68, 18, 58};
SDL_Color colorPink = { 255, 146, 198};

SDL_Color *dotColors[DOT_COLORS] = {
        &colorRed,
        &colorOrange,
        &colorGreen,
        &colorBlue,
        &colorIndigo,
        &colorViolet,
        &colorGrey,
        &colorPink,
        &colorPeach
};
