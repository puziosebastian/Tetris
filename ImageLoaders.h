#ifndef IMAGELOADERS_H
#define IMAGELOADERS_H
extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}

SDL_Surface* getBlueBlock();
SDL_Surface* getYellowBlock();
SDL_Surface* getOrangeBlock();
SDL_Surface* getGreenBlock();
SDL_Surface* getLightBlueBlock();
SDL_Surface* getRedBlock();
SDL_Surface* getPurpleBlock();

void loadImages();
#endif //IMAGELOADERS_H