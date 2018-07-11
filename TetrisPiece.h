#ifndef TETRISPIECE_H
#define TETRISPIECE_H
extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}
#include "GameState.h"
struct Map; // struktura mapa

enum PieceType{ // typ piecu; (jeden z 7)
LINE,
PODIUM,
BOX,
L,
REVERSE_L,
STAIRS,
REVERSE_STAIRS
};

struct TetrisPiece{   // klocek (zlozony z 4)
   struct TetrisBlock** blocks;
   bool shouldSplit; // czy ma byc rozdzielony
   float rotation; // kat 
   PieceType type; // typ klocka
};
TetrisPiece* tetris_piece_create(PieceType type); // tworzenie klocka

void tetris_piece_set_position(struct TetrisPiece* piece, float x, float y); // ustawienie pozycji

bool tetris_piece_detect_collision(TetrisPiece* piece, Map* map);  // wykrywanie kolizji

void tetris_piece_move_vertically(struct TetrisPiece* piece, float y, Map* map); // ruch w pionie

void drawPiece(SDL_Surface *screen, TetrisPiece *piece);  // rysowanie klocka (z 4 poj)

void tetris_piece_next_piece(TetrisPiece* piece, PieceType type); // nastepny klocek

void tetris_piece_move_horizontally(struct TetrisPiece* piece, float x, Map* map); // ruch w poziomie

PieceType tetris_piece_random(); // losowanie typu klocka

void tetris_piece_rotate(TetrisPiece* piece);  // obrot klocka

void tetris_piece_instant_drop(TetrisPiece* piece, Map* map);  // natychmiastowe opadanie

bool tetris_piece_is_in_bounds(TetrisPiece* piece, Map* map);  // sprawdzenie czy klocek jest w calosci na planszy

void tetris_piece_update_image(TetrisPiece *piece, float deltaTime);  // aktualizacja obrazu klocka

void tetris_save(TetrisPiece* piece, Map* map, GameState state);

void tetris_load(TetrisPiece* piece, Map* map, GameState state);
#endif //TETRISPIECE_H