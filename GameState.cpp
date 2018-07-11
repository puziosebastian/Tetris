#include "GameState.h"
#include <stdlib.h>
#include <assert.h>

GameState* game_state_create(float speed, float timeLimit) {    
	GameState* newState = (GameState*)malloc(sizeof(GameState));
	assert(newState != NULL);
	newState->speed = speed;  
	newState->speedMultiplier = 1;  
	newState->time = 0;  
	newState->timeLimit = timeLimit; 
	newState->points = 0;  
	newState->quadrupleRowDeletion = 0;  
	return newState;
}

void game_state_destroy(GameState* state) {
	if (state != NULL)
		free(state);
}

void game_state_update(GameState* state, float deltaTime) {
	state->time += deltaTime;
	if (state->time >= state->timeLimit){
		state->speedMultiplier++;
		state->time = 0;
	}
}

void game_state_restart(GameState* state) {
	state->speed = SPEED;
	state->speedMultiplier = 1;
	state->time = 0;
	state->timeLimit = TIMELIMIT;
	state->points = 0;
	state->quadrupleRowDeletion = 0;
}