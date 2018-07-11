#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "DrawFunctions.h"
extern "C" {
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
}
#include "Defines.h"
#include "GameState.h"
#include "TetrisBlock.h"
#include "TetrisPiece.h"
#include "ImageLoaders.h"
#include "Map.h"

void numberToString(char * string, int n);

int main(int argc, char **argv) {
	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps;

	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *eti;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	loadImages();
	TetrisPiece *piece = tetris_piece_create(PieceType::LINE);
	Map *map = map_create();
	GameState* state = game_state_create(SPEED, TIMELIMIT);

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe³noekranowy
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "TETRIS");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;

	while((!quit)) {
		t2 = SDL_GetTicks();
		
		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		worldTime += delta;

		SDL_FillRect(screen, NULL, black);

		// obs³uga spadania klocków
		tetris_piece_update_image(piece, delta);
		map_update_block_images( map, delta);
		drawPiece(screen, piece);
		tetris_piece_move_vertically(piece, state->speed * state->speedMultiplier * delta, map);
		game_state_update(state, delta);
		if (piece->shouldSplit){
			map_split_piece(piece, map);
			tetris_piece_next_piece(piece, tetris_piece_random());
		}
		map_erase_full_lines(map,state);
		map_draw(screen, map);

		// naniesienie wyniku rysowania na rzeczywisty ekran
		fpsTimer += delta;
		if(fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
			};

		// tekst informacyjny
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, red, blue);
		sprintf(text, "Tetris, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		sprintf(text, "Punkty:");
		DrawString(screen, (screen->w / 2 - strlen(text) * 8 / 2) - 250, 26, text, charset);
		numberToString(text, state->points);
		DrawString(screen, (screen->w / 2 - strlen(text) * 8 / 2) - 195, 26, text, charset);
		sprintf(text, "s - zapis, l - odczyt, z - nastepny poziom, n - od nowa");
		DrawString(screen, (screen->w / 2 - strlen(text) * 8 / 2) + 45, 26, text, charset);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y)
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_DOWN){
						if (tetris_piece_is_in_bounds(piece, map))
							tetris_piece_instant_drop(piece, map);
					}
					else if (event.key.keysym.sym == SDLK_RIGHT) tetris_piece_move_horizontally(piece, 32, map);
					else if (event.key.keysym.sym == SDLK_LEFT) tetris_piece_move_horizontally(piece, -32, map);
					else if (event.key.keysym.sym == SDLK_SPACE){
						if (tetris_piece_is_in_bounds(piece, map))
							tetris_piece_rotate(piece);
					}
					else if (event.key.keysym.sym == SDLK_s) tetris_save(piece, map, *state);
					else if (event.key.keysym.sym == SDLK_z) state->speedMultiplier++;
					else if (event.key.keysym.sym == SDLK_n){
						game_state_restart(state);
						map_restart(map);
					}
					else if (event.key.keysym.sym == SDLK_l) tetris_save(piece, map, *state);
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
		};
		frames++;
		};

	// zwolnienie powierzchni
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};

void numberToString(char * string, int n) {
	int i = 0;
	int tmp = n;

	while (tmp != 0) {
		tmp /= 10;
		i++;
	}

	if (n < 0) {
		printf("Blad w numberToString : n < 0\n");
		exit(1);
	}

	if (n == 0) {
		string[0] = '0';
		string[1] = '\0';
		return;
	}

	string[i] = '\0';
	while (n > 0) {
		i--;
		int nextSign = n % 10;
		n /= 10;
		string[i] = nextSign + '0';
	}
}
