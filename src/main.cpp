#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "res_path.h"
#include "event_handler.h"

int SCREEN_WIDTH, SCREEN_HEIGHT;
bool exit_game_loop = false;

const int win_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

const std::string resource_path = getResourcePath();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect *clip, SDL_Rect *dst);
void updateDisplay(SDL_Window* win);

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *win = SDL_CreateWindow("Getting Loopy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);

	updateDisplay(win);

	SDL_Renderer *ren = SDL_GetRenderer(win); 

	SDL_Event event;
	EventHandler handler;
	while (!exit_game_loop){
		while (SDL_PollEvent(&event)){
			exit_game_loop = handler.handleEvent(event);
		}

		SDL_SetRenderDrawColor(ren, 50, 50, 100, 255);
		SDL_RenderClear(ren);

		SDL_RenderPresent(ren);

		std::string error;
		if ((error=SDL_GetError()) != "") { std::cout << error << std::endl; }
	}

	SDL_Quit();

	return 0;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect *clip, SDL_Rect *dst) {
	SDL_RenderCopy(ren, tex, clip, dst);
}

void updateDisplay(SDL_Window* win) {
	SDL_Rect r;
	SDL_GetDisplayUsableBounds(0, &r);
	SCREEN_WIDTH = r.w;
	SCREEN_HEIGHT = r.h;
	SDL_SetWindowSize(win, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Surface* surface = SDL_GetWindowSurface(win);
}
