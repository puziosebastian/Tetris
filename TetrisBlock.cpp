#include "TetrisBlock.h"
#include <assert.h>
#include "Defines.h"
#include <math.h>

TetrisBlock* tetris_block_create(){
   TetrisBlock* newBlock = (TetrisBlock*)malloc(sizeof(TetrisBlock));
   assert(newBlock != NULL);
   return newBlock;
}

void tetris_block_destroy(TetrisBlock* block){
	if (block != NULL)
		free(block);
}

void tetris_block_set_position(struct TetrisBlock* block, float x, float y){
   block->position.x = x;
   block->position.y = y;
}

void tetris_block_move(struct TetrisBlock* block, float x, float y){
   block->position.x += x;
   block->position.y += y;
}

void getVertices(Point vertices[4], TetrisBlock* block){
	vertices[0].x = block->position.x - block->surface->w / 2;
	vertices[0].y = block->position.y - block->surface->h / 2;

	vertices[1].x = block->position.x + block->surface->w / 2;
	vertices[1].y = block->position.y - block->surface->h / 2;

	vertices[2].x = block->position.x + block->surface->w / 2;
	vertices[2].y = block->position.y + block->surface->h / 2;

	vertices[3].x = block->position.x - block->surface->w / 2;
	vertices[3].y = block->position.y + block->surface->h / 2;
}

bool block_intersects(TetrisBlock* block1, TetrisBlock* block2){
	Point block1Vertices[4];
	getVertices(block1Vertices, block1);
	int x = block2->position.x - block2->surface->w / 2;
	int y = block2->position.y - block2->surface->h / 2;
	int w = block2->surface->w;
	int h = block2->surface->h;
	for (int i = 0; i < 4; i++){
		if (block1Vertices[i].y >= y && block1Vertices[i].y <= y + h)
		if (block1Vertices[0].x == x && block1Vertices[1].x == x + w)
			return true;
	}
	return false;
}

void tetris_block_update_image(TetrisBlock *block, float deltaTime){
	if (fabs(block->imagePosition.x - block->imageDestination.x) < 2){
		block->imagePosition.x = block->imageDestination.x;
	}
	if (fabs(block->imagePosition.y - block->imageDestination.y) < 2){
		block->imagePosition.y = block->imageDestination.y;
	}
	if (block->imagePosition.x < block->imageDestination.x){
		block->imagePosition.x += deltaTime * MOVEMENT_SPEED;
	}
	if (block->imagePosition.x > block->imageDestination.x){
		block->imagePosition.x -= deltaTime * MOVEMENT_SPEED;
	}
	if (block->imagePosition.y < block->imageDestination.y){
		block->imagePosition.y += deltaTime * MOVEMENT_SPEED;
	}
	if (block->imagePosition.y > block->imageDestination.y){
		block->imagePosition.y -= deltaTime * MOVEMENT_SPEED;
	}
}

