#ifndef MAP_H
#define MAP_H
#include "TetrisPiece.h"
#include "TetrisBlock.h"
#include "Defines.h"
#include "GameState.h"
#include <assert.h>
struct Map{
	int x;
	int y;
	TetrisBlock* map[SCREEN_HEIGHT/32][SCREEN_WIDTH/32];  // mapa sklada sie z siatki o poj kwadracie 32x32
};

Map* map_create();  // tworzenie mapy

void map_split_piece(TetrisPiece *piece, Map* map);  // podzial klocka na bloki po upadku

void map_draw(SDL_Surface* screen, Map* map);  // rysowanie mapy

void map_erase_full_lines(Map* map, GameState * state);  // usuwanie pelnych wierszy

void map_update_block_images(Map* map, float deltaTime);  // aktualizacja obrazu bloku na mapie

void map_restart(Map* map);  // restart mapy

#endif
