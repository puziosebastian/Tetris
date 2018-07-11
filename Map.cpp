#include "Map.h"
#include "TetrisBlock.h"
#include "DrawFunctions.h"
#include "TetrisBlock.h"
#include "ImageLoaders.h"
#include "GameState.h"
Map* map_create(){
	Map* newMap = (Map*)malloc(sizeof(Map));
	assert(newMap != NULL);

	int y = SCREEN_HEIGHT / 32;
	int x = SCREEN_WIDTH / 32;
	newMap->x = x;
	newMap->y = y;
	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++)
			newMap->map[i][j] = NULL;
	}
	for (int i = 0; i < x; i++){
		TetrisBlock *newBlock = tetris_block_create();
		newBlock->surface = getRedBlock();
		newBlock->position.x = newBlock->imagePosition.x = i * 32 + 16;
		newBlock->position.y = newBlock->imagePosition.y = SCREEN_HEIGHT - 16;
		newMap->map[y - 1][i] = newBlock;
	}

	for (int i = 0; i < y; i++){
		TetrisBlock *newBlock = tetris_block_create();
		newBlock->surface = getRedBlock();
		newBlock->position.x = newBlock->imagePosition.x = 16;
		newBlock->position.y = newBlock->imagePosition.y = i * 32 + 16;
		newMap->map[i][0] = newBlock;

		newBlock = tetris_block_create();
		newBlock->surface = getRedBlock();
		newBlock->position.x = newBlock->imagePosition.x = SCREEN_WIDTH - 16;
		newBlock->position.y = newBlock->imagePosition.y = i * 32 + 16;
		newMap->map[i][x-1] = newBlock;
	}

	return newMap;
}

void map_split_piece(TetrisPiece *piece, Map* map){
	for (int i = 0; i < 4; i++){
		int x = piece->blocks[i]->position.x;
		x /= 32;
		piece->blocks[i]->position.x = x * 32 + 16;
		int y = piece->blocks[i]->position.y;
		y /= 32;
		piece->blocks[i]->position.y = y * 32 + 16;

		map->map[y][x] = piece->blocks[i];
	}
}

void map_draw(SDL_Surface* screen, Map* map){
	for (int i = 0; i < map->y; i++){
		for (int j = 0; j < map->x; j++){
			if (map->map[i][j] != NULL){
				SDL_Surface *sprite = map->map[i][j]->surface;
				int x = map->map[i][j]->imagePosition.x;
				int y = map->map[i][j]->imagePosition.y;
				DrawSurface(screen, sprite, x, y);
			}
		}
	}
}

void map_shift_blocks(Map* map, int y){
	for (int i = y; i > 1; i--){
		for (int j = 1; j < map->x-1; j++){
			map->map[i][j] = map->map[i - 1][j];
			if (map->map[i][j] != NULL)
				map->map[i][j]->imageDestination.y += 32;
			if (map->map[i][j] != NULL)
				map->map[i][j]->position.y += 32;
			if (map->map[i][j] != NULL)
				map->map[i][j]->imagePosition.y += 32;
		}
	}
}

void map_update_block_images(Map* map, float deltaTime){
	for (int i = 0; i < map->y - 1; i++){
		for (int j = 1; j < map->x - 1; j++){
			if (map->map[i][j] != NULL){
				tetris_block_update_image(map->map[i][j], deltaTime);
			}
		}
	}
}

void map_erase_full_lines(Map* map, GameState * state){
	int liczbaUsuwanychWierszy = 0;
	for (int i = 0; i < map->y-1; i++){
		for (int j = 1; j < map->x - 1; j++){
			if (map->map[i][j] == NULL)
				break;
			if (j == map->x - 2)
				liczbaUsuwanychWierszy++;
		}
	}

	switch (liczbaUsuwanychWierszy){
	case 0: break;
	case 1:	state->points += state->speedMultiplier * 100;
			state->quadrupleRowDeletion = 0;
		break;
	case 2: state->points += state->speedMultiplier * 200;
			state->quadrupleRowDeletion = 0;
		break;
	case 3: state->points += state->speedMultiplier * 400;
			state->quadrupleRowDeletion = 0;
		break;
	case 4:
		if (state->quadrupleRowDeletion > 0)
			state->points += state->speedMultiplier * 1200;
		else
			state->points += state->speedMultiplier * 800;
			state->quadrupleRowDeletion++;
		break;
	default: break;
	}

	for (int i = 1; i < map->y - 1; i++){
		int j;
		for (j = 1; j < map->x - 1; j++){
			if (map->map[i][j] == NULL){
				j = 0;
				break;
			}
		}
		if (j == map->x - 1){
			for (j = 1; j < map->x - 1; j++)
				tetris_block_destroy(map->map[i][j]);
			    map_shift_blocks(map, i);
		}
	}
}

void map_restart(Map* map) {
	for (int i = 1; i < map->y - 1; i++) {
		for (int j = 1; i < map->x - 1; j++) {
			tetris_block_destroy(map->map[i][j]);
		}
	}
}