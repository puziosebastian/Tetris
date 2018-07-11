#include "ImageLoaders.h"
extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}
SDL_Surface* blueBlock;
SDL_Surface* yellowBlock;
SDL_Surface* greenBlock;
SDL_Surface* lightBlueBlock;
SDL_Surface* orangeBlock;
SDL_Surface* redBlock;
SDL_Surface* purpleBlock;

void loadImages(){
	blueBlock = SDL_LoadBMP("bmp/tetris_block_blue_32.bmp");
	yellowBlock = SDL_LoadBMP("bmp/tetris_block_yellow_32.bmp");
	greenBlock = SDL_LoadBMP("bmp/tetris_block_green_32.bmp");
	lightBlueBlock = SDL_LoadBMP("bmp/tetris_block_light_blue_32.bmp");
	orangeBlock = SDL_LoadBMP("bmp/tetris_block_orange_32.bmp");
	redBlock = SDL_LoadBMP("bmp/tetris_block_red_32.bmp");
	purpleBlock = SDL_LoadBMP("bmp/tetris_block_purple_32.bmp");
}

SDL_Surface* getBlueBlock(){
	return blueBlock;
}

SDL_Surface* getYellowBlock(){
	return yellowBlock;
}
SDL_Surface* getOrangeBlock(){
	return orangeBlock;
}
SDL_Surface* getGreenBlock(){
	return greenBlock;
}
SDL_Surface* getLightBlueBlock(){
	return lightBlueBlock;
}
SDL_Surface* getRedBlock(){
	return redBlock;
}
SDL_Surface* getPurpleBlock(){
	return purpleBlock;
}