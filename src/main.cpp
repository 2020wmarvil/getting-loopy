#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "res_path.h"
#include "event_handler.h"
#include "renderer.h"
#include "entity.h"
#include "player.h"

int DEFAULT_SCREEN_WIDTH = 100;
int DEFAULT_SCREEN_HEIGHT = 100;

bool exit_game_loop = false;

const int win_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

const std::string resource_path = getResourcePath();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect *clip, SDL_Rect *dst);
void updateDisplay(SDL_Window* win);

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *win = SDL_CreateWindow("Getting Loopy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, win_flags);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Renderer renderer(ren, win);
	renderer.setGroundTexture(resource_path + "ground.png");

	Player player(0, 0, renderer.loadTexture(resource_path + "player.png"));

	SDL_Event event;
	EventHandler handler;
	while (!exit_game_loop){
		while (SDL_PollEvent(&event)){
			exit_game_loop = handler.handleEvent(event);
		}

		renderer.clear();
		renderer.render(player);
		renderer.renderGround();
		renderer.present();

		std::string error;
		if ((error=SDL_GetError()) != "") { std::cout << error << std::endl; }
	}

	SDL_Quit();

	return 0;
}
