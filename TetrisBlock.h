#ifndef TETRISBLOCK_H
#define TETRISBLOCK_H
extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}

struct Position{
   float x, y;
};

typedef Position Point;

struct TetrisBlock{  // kazdy blok ma 3 ''wymiary''
   struct Position position;  // realna pozycja bloku
   struct Position imagePosition;  // pozycja obrazka bloku (plynny ruch)
   struct Position imageDestination;  // pozycja celu bloku (plynny spadek w dol)
   SDL_Surface *surface;
};
TetrisBlock* tetris_block_create();  // tworzenie poj bloku

void block_set_position(struct TetrisBlock* block, float x, float y);  // ustawienie pozycji bloczka

void tetris_block_destroy(TetrisBlock* block);  // niszczenie poj blokow

void tetris_block_move(struct TetrisBlock* block, float x, float y);  // ruch bloku

void getVertices(Point vertices[4], TetrisBlock* block);  // pobranie wierzcholkow bloku (do sprawdzenia kolizji)

bool block_intersects(TetrisBlock* block1, TetrisBlock* block2);  // kolizja miedzy blokami

void tetris_block_update_image(TetrisBlock *block, float deltaTime);  // aktualizacja obrazu bloku

#endif //TETRISBLOCK_H