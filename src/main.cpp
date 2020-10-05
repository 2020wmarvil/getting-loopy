#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "res_path.h"
#include "event_handler.h"
#include "renderer.h"
#include "collider.h"
#include "entity.h"
#include "player.h"
#include "track.h"

const int FPS = 60; 
const int TICKS_PER_FRAME = 1000 / FPS;

const int win_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

const std::string resource_path = getResourcePath();

unsigned int entity_ID_counter = 0;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect *clip, SDL_Rect *dst);
void updateDisplay(SDL_Window* win);

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *win = SDL_CreateWindow("Getting Loopy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 100, 100, win_flags);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	Renderer renderer(ren, win);
	renderer.setGroundTexture(resource_path + "ground.png");

	Collider collider;

	Player player(0, 10, 0, renderer.loadTexture(resource_path + "player.png"), entity_ID_counter++);
	collider.addEntity(&player);

	// move this into a level.h file
	double track_length = 1.0;
	int num_tracks = 30, radius = 5;
	std::vector<Track*> tracks;
	for (double i=0; i<num_tracks; i++) {
		double theta = (i / (num_tracks / 2)) * M_PI;

		double x = radius * cos(theta);
		double y = radius * sin(theta) + player.getY();
	
		Track *track = new Track(x, y, M_PI / 2 - theta, track_length, renderer.loadTexture(resource_path + "track.png"), entity_ID_counter++);
		tracks.push_back(track);

		collider.addEntity(track);
	}

	SDL_Event event;
	EventHandler handler(&player);

	Uint8 tick_initial = SDL_GetTicks();
	Uint8 tick_final = SDL_GetTicks();

	bool exit_game_loop = false;
	while (!exit_game_loop){
		while (SDL_PollEvent(&event)){
			exit_game_loop = handler.handleEvent(event);
		}

		tick_final = SDL_GetTicks();
		Uint8 tick_delta = tick_final - tick_initial;

		if (tick_delta > TICKS_PER_FRAME) {
			tick_initial = tick_final;

			double dt = tick_delta / 1000.0;

			// only check for collisions against entities in the current and previous levels
			// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
			std::vector<Collision*> collided = collider.collide(&player);
			std::cout << collided.size() << std::endl;

			if (!player.update(dt, collided)) { break; }

			renderer.clear();

			renderer.render(player);
			for (Track *track : tracks) renderer.render(*track);
			renderer.renderGround();

			renderer.present();
		}

		std::string error;
		if ((error=SDL_GetError()) != "") { std::cout << error << std::endl; }
	}

	SDL_Quit();

	return 0;
}
