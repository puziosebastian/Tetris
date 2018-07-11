
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include "TetrisBlock.h"
extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}
#include "ImageLoaders.h"
#include "TetrisPiece.h"
#include "DrawFunctions.h"
#include "Defines.h"
#include "Map.h"
void tetris_piece_init_blocks(TetrisPiece* piece, PieceType type){
	switch (type){
	case LINE:
		for (int i = 0; i < 4; i++){
			piece->blocks[i]->surface = getRedBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = 304;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = i * 32 - 112;
		}
		break;
	case PODIUM:
		for (int i = 0; i < 3; i++){
			piece->blocks[i]->surface = getOrangeBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = i * 32 + 272;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = -48;
		}
		piece->blocks[3]->surface = getOrangeBlock();
		piece->blocks[3]->position.x = piece->blocks[3]->imagePosition.x = piece->blocks[3]->imageDestination.x = 304;
		piece->blocks[3]->position.y = piece->blocks[3]->imagePosition.y = piece->blocks[3]->imageDestination.y = -16;
		break;
	case BOX:
		piece->blocks[0]->surface = getLightBlueBlock();
		piece->blocks[0]->position.x = piece->blocks[0]->imagePosition.x = piece->blocks[0]->imageDestination.x = 304;
		piece->blocks[0]->position.y = piece->blocks[0]->imagePosition.y = piece->blocks[0]->imageDestination.y = -48;
		piece->blocks[1]->surface = getLightBlueBlock();
		piece->blocks[1]->position.x = piece->blocks[1]->imagePosition.x = piece->blocks[1]->imageDestination.x = 304 + 32;
		piece->blocks[1]->position.y = piece->blocks[1]->imagePosition.y = piece->blocks[1]->imageDestination.y = -48;
		piece->blocks[2]->surface = getLightBlueBlock();
		piece->blocks[2]->position.x = piece->blocks[2]->imagePosition.x = piece->blocks[2]->imageDestination.x = 304;
		piece->blocks[2]->position.y = piece->blocks[2]->imagePosition.y = piece->blocks[2]->imageDestination.y = -16;
		piece->blocks[3]->surface = getLightBlueBlock();
		piece->blocks[3]->position.x = piece->blocks[3]->imagePosition.x = piece->blocks[3]->imageDestination.x = 304 + 32;
		piece->blocks[3]->position.y = piece->blocks[3]->imagePosition.y = piece->blocks[3]->imageDestination.y = -16;
		break;
	case L:
		for (int i = 0; i < 3; i++) {
			piece->blocks[i]->surface = getYellowBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = 304;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = i * 32 - 80;
		}
		piece->blocks[3]->surface = getYellowBlock();
		piece->blocks[3]->position.x = piece->blocks[3]->imagePosition.x = piece->blocks[3]->imageDestination.x = 336;
		piece->blocks[3]->position.y = piece->blocks[3]->imagePosition.y = piece->blocks[3]->imageDestination.y = -16;
		break;
	case REVERSE_L:
		for (int i = 0; i < 3; i++) {
			piece->blocks[i]->surface = getPurpleBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = 304;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = i * 32 - 80;
		}
		piece->blocks[3]->surface = getPurpleBlock();
		piece->blocks[3]->position.x = piece->blocks[3]->imagePosition.x = piece->blocks[3]->imageDestination.x = 272;
		piece->blocks[3]->position.y = piece->blocks[3]->imagePosition.y = piece->blocks[3]->imageDestination.y = -16;
		break;
	case STAIRS:
		for (int i = 0; i < 2; i++) {
			piece->blocks[i]->surface = getBlueBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = i * 32 + 304;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = 0;
		}
		for (int i = 2; i < 4; i++) {
			piece->blocks[i]->surface = getBlueBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = i * 32 + 208;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = 32;
		}
		break;
	case REVERSE_STAIRS:	
		for (int i = 0; i < 2; i++) {
			piece->blocks[i]->surface = getGreenBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = i * 32 + 272;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = 0;
		}
		for (int i = 2; i < 4; i++) {
			piece->blocks[i]->surface = getGreenBlock();
			piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = i * 32 + 240;
			piece->blocks[i]->position.y = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = 32;
		}
		break;
	}
}

TetrisPiece* tetris_piece_create(PieceType type){
	TetrisPiece* newPiece;
	newPiece = (TetrisPiece*)malloc(sizeof(TetrisPiece));
	assert(newPiece != NULL);
	newPiece->shouldSplit = false;
	newPiece->rotation = 0;
	newPiece->type = type;
	newPiece->blocks = (TetrisBlock**)malloc(sizeof(TetrisBlock*)* 4);
	assert(newPiece->blocks != NULL);
	for (int i = 0; i < 4; i++)
		newPiece->blocks[i] = tetris_block_create();

	tetris_piece_init_blocks(newPiece, type);
	return newPiece;
}

void tetris_piece_next_piece(TetrisPiece* piece, PieceType type){
	piece->shouldSplit = false;
	piece->rotation = 0;
	piece->type = type;
	piece->blocks = (TetrisBlock**)malloc(sizeof(TetrisBlock*)* 4);
	assert(piece->blocks != NULL);
	for (int i = 0; i < 4; i++)
		piece->blocks[i] = tetris_block_create();

	tetris_piece_init_blocks(piece, type);
}

void tetris_piece_set_position(struct TetrisPiece* piece, float x, float y){
	for (int i = 0; i < 4; i++){
		piece->blocks[i]->position.x = x;
		piece->blocks[i]->position.y = i * 32 + y;
	}
}

bool tetris_piece_detect_collision(TetrisPiece* piece, Map* map){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < map->y; j++){
			for (int k = 0; k < map->x; k++)
			if (map->map[j][k] != NULL)
			if (block_intersects((piece->blocks[i]), map->map[j][k]))
				return true;
		}
	}
	return false;
}

void tetris_piece_move_vertically(struct TetrisPiece* piece, float y, Map* map){
	if (tetris_piece_detect_collision(piece, map)){
		piece->shouldSplit = true;
		return;
	}

	for (int i = 0; i < 4; i++)
	if (piece->blocks[i]->position.y >= SCREEN_HEIGHT - 48){
		piece->blocks[i]->position.y = SCREEN_HEIGHT - 48;
		piece->shouldSplit = true;
		return;
	}

	for (int i = 0; i < 4; i++){
		piece->blocks[i]->position.y += y;
		piece->blocks[i]->imageDestination.y += y;
		piece->blocks[i]->imagePosition.y += y;
	}
}

void tetris_piece_move_horizontally(struct TetrisPiece* piece, float x, Map* map){
	float prevX[4];
	for (int i = 0; i < 4; i++)
		prevX[i] = piece->blocks[i]->position.x;

	for (int i = 0; i < 4; i++)
		piece->blocks[i]->position.x += x;

	if (tetris_piece_detect_collision(piece, map)){
		for (int i = 0; i < 4; i++)
			piece->blocks[i]->position.x = prevX[i];
	}
	else {
		for (int i = 0; i < 4; i++)
			piece->blocks[i]->imageDestination.x += x;
	}
}

void drawPiece(SDL_Surface *screen, TetrisPiece *piece){
	for (int i = 0; i < 4; i++){
		SDL_Surface *sprite = piece->blocks[i]->surface;
		int x = piece->blocks[i]->imagePosition.x;
		int y = piece->blocks[i]->imagePosition.y;
		DrawSurface(screen, sprite, x, y);
	}
}

void tetris_piece_update_image(TetrisPiece *piece, float deltaTime){
	if (piece->blocks[0]->imagePosition.x < piece->blocks[0]->imageDestination.x){
		for (int i = 0; i < 4; i++){
			piece->blocks[i]->imagePosition.x += deltaTime * MOVEMENT_SPEED;
		}
	}
	if (piece->blocks[0]->imagePosition.x > piece->blocks[0]->imageDestination.x){
		for (int i = 0; i < 4; i++){
			piece->blocks[i]->imagePosition.x -= deltaTime * MOVEMENT_SPEED;
		}
	}
	if (piece->blocks[0]->imagePosition.y > piece->blocks[0]->imageDestination.y){
		for (int i = 0; i < 4; i++){
			piece->blocks[i]->imagePosition.y -= deltaTime * MOVEMENT_SPEED;
		}
	}
	if (piece->blocks[0]->imagePosition.y < piece->blocks[0]->imageDestination.y){
		for (int i = 0; i < 4; i++){
			piece->blocks[i]->imagePosition.y += deltaTime * MOVEMENT_SPEED;
		}
	}
}

PieceType tetris_piece_random(){
	switch (rand() % 7){
	case 0:
		return PieceType::LINE;
	case 1:
		return PieceType::PODIUM;
	case 2:
		return PieceType::BOX;
	case 3:
		return PieceType::L;
	case 4:
		return PieceType::REVERSE_L;
	case 5:
		return PieceType::STAIRS;
	case 6:
		return PieceType::REVERSE_STAIRS;
	default:
		return PieceType::LINE;
	}
}

void tetris_piece_rotate(TetrisPiece* piece){
    static bool snap_dir;
    Point center;

    switch (piece->type){
    case LINE:
        center.x = piece->blocks[2]->position.x;
        center.y = piece->blocks[2]->position.y;
        break;
    case PODIUM:
        center.x = piece->blocks[1]->position.x;
        center.y = piece->blocks[1]->position.y;
        break;
    case BOX:
        return;
        break;
    case L:
        center.x = piece->blocks[1]->position.x;
        center.y = piece->blocks[1]->position.y;
        break;
    case REVERSE_L:
        center.x = piece->blocks[1]->position.x;
        center.y = piece->blocks[1]->position.y;
        break;
    case STAIRS:
        center.x = piece->blocks[0]->position.x;
        center.y = piece->blocks[0]->position.y;
        break;
    case REVERSE_STAIRS:
        center.x = piece->blocks[1]->position.x;
        center.y = piece->blocks[1]->position.y;
        break;
    }

    float rotation = -piece->rotation;
    for (int i = 0; i < 4; i++){
        float x = piece->blocks[i]->position.x;
        float y = piece->blocks[i]->position.y;
        piece->blocks[i]->position.x = center.x + (x - center.x)*cos(rotation) + (y - center.y)*sin(rotation);
        piece->blocks[i]->position.y = center.y + (x - center.x)*sin(rotation) * -1 + (y - center.y)*cos(rotation);
        int gridX = piece->blocks[i]->position.x / 32;
        int gridY = piece->blocks[i]->position.y / 32;
        piece->blocks[i]->position.x = gridX * 32 + 16;
        piece->blocks[i]->position.y = gridY * 32 + 16;
    }

    piece->rotation += M_PI / 2;
    if (piece->rotation >= 2 * M_PI)
        piece->rotation = 0;
    rotation = piece->rotation;
    for (int i = 0; i < 4; i++){
        float x = piece->blocks[i]->position.x;
        float y = piece->blocks[i]->position.y;
        piece->blocks[i]->position.x = center.x + (x - center.x)*cos(rotation) + (y - center.y)*sin(rotation);
        piece->blocks[i]->position.y = center.y + (x - center.x)*sin(rotation) * -1 + (y - center.y)*cos(rotation);
        int gridX = piece->blocks[i]->position.x / 32;
        int gridY = piece->blocks[i]->position.y / 32;
        piece->blocks[i]->position.x = piece->blocks[i]->imagePosition.x = piece->blocks[i]->imageDestination.x = gridX * 32 + 16;
        piece->blocks[i]->position.y  = piece->blocks[i]->imagePosition.y = piece->blocks[i]->imageDestination.y = gridY * 32 + 16;
    }
}

void tetris_piece_instant_drop(TetrisPiece* piece, Map* map){
	for (int i = 0; i < 4; i++){
		int gridX = piece->blocks[i]->position.x / 32;
		int gridY = piece->blocks[i]->position.y / 32;
		piece->blocks[i]->position.x = gridX * 32 + 16;
		piece->blocks[i]->position.y = gridY * 32 + 16;
	}

	while (!tetris_piece_detect_collision(piece, map)){
		for (int i = 0; i < 4; i++)
			piece->blocks[i]->position.y += 32;
	}
	for (int i = 0; i < 4; i++)
		piece->blocks[i]->imageDestination = piece->blocks[i]->position;
	    piece->shouldSplit = true;
}


bool tetris_piece_is_in_bounds(TetrisPiece* piece, Map* map){
	for (int i = 0; i < 4; i++){
		int gridX = piece->blocks[i]->position.x / 32;
		int gridY = piece->blocks[i]->position.y / 32;
		if (gridX < 0 || gridY < 1 || gridX > map->x - 1 || gridY > map->y - 1)
			return false;
	}
	return true;
}

void tetris_save(TetrisPiece* piece, Map* map, GameState state) {
	FILE * file = fopen("save.txt", "w");
	if (file != NULL) {
		fprintf(file, "%d %d %f %f %f %f\n",
			state.points,
			state.quadrupleRowDeletion,
			state.speed,
			state.speedMultiplier,
			state.time,
			state.timeLimit);

		fprintf(file, "%f %d %d",
			piece->rotation,
			piece->shouldSplit,
			(int)piece->type
			);
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				fprintf(file, "%f %f ", piece->blocks[y][x].position.x, piece->blocks[y][x].position.y);
			}
			fprintf(file, "\n");
		}

		for (int y = 0; y < map->y; y++) {
			for (int x = 0; x < map->x; x++) {
				if (map->map[y][x] != NULL) {
					fprintf(file, "%f %f ", map->map[y][x]->position.x, map->map[y][x]->position.y);
				}
				else {
					fprintf(file, "%f %f ", -1, -1);
				}
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}
}

void tetris_load(TetrisPiece* piece, Map* map, GameState state) {
	FILE * file = fopen("save.txt", "r");
	if (file != NULL) {
		fscanf(file, "%d %d %f %f %f %f\n",
			state.points,
			state.quadrupleRowDeletion,
			state.speed,
			state.speedMultiplier,
			state.time,
			state.timeLimit);

		fscanf(file, "%f %d %d",
			piece->rotation,
			piece->shouldSplit,
			(int)piece->type
			);
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				fscanf(file, "%f %f ", piece->blocks[y][x].position.x, piece->blocks[y][x].position.y);
			}
			fscanf(file, "\n");
		}

		for (int y = 0; y < map->y; y++) {
			for (int x = 0; x < map->x; x++) {
				if (map->map[y][x] != NULL) {
					fscanf(file, "%f %f ", map->map[y][x]->position.x, map->map[y][x]->position.y);
				}
				else {
					fscanf(file, "%f %f ", -1, -1);
				}
			}
			fscanf(file, "\n");
		}
		fclose(file);
	}
}
