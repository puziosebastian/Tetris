#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <stdlib.h>
#include "Defines.h"

struct GameState{  // stan gry
	float speed;  // predkosc poczatkowa
	float speedMultiplier;  // mnoznik predkosci po czasie
	float time;  // czas pocz
	float timeLimit;  // czas po ktorym predkosc wzrasta
	int points;  // punkty
	int quadrupleRowDeletion;  // liczba poczwornych zniszczonych wierszy
};

GameState* game_state_create(float speed, float timeLimit);  // tworzenie stanu gry

void game_state_destroy(GameState* state);  // usuniecie stanu

void game_state_update(GameState* state, float deltaTime);  // zaktualizowanie

void game_state_restart(GameState* state);

#endif