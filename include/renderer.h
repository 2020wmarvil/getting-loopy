#pragma once

#define VIEWPORT_SIZE 100

#include "entity.h"

class Renderer {
private:
	int SCREEN_WIDTH, SCREEN_HEIGHT, VIEWPORT_SCALAR;

	SDL_Renderer* renderer;
public:
	Renderer(SDL_Renderer* renderer, SDL_Window* window) : renderer(renderer) {
		updateDisplay(window);
	}

	void render(const Entity& entity) {
		Texture texture = entity.getTexture();

		SDL_Rect dst = texture.dst;
		dst.x *= VIEWPORT_SCALAR; dst.y *= VIEWPORT_SCALAR;
		dst.w *= VIEWPORT_SCALAR; dst.h *= VIEWPORT_SCALAR;

		dst.y = SCREEN_HEIGHT - dst.y - dst.h;
	
        	SDL_RenderCopy(this->renderer, texture.texture, &texture.clip, &dst);
	}

	void clear() {
		SDL_SetRenderDrawColor(this->renderer, 50, 50, 100, 255); 
		SDL_RenderClear(this->renderer);
	}

	void present() {
		SDL_RenderPresent(this->renderer);
	}

	SDL_Texture* loadTexture(const std::string &file) {
        	return IMG_LoadTexture(this->renderer, file.c_str());
	}

	void updateDisplay(SDL_Window* win) {
		SDL_Rect r;
		SDL_GetDisplayUsableBounds(0, &r);
		SCREEN_WIDTH = r.w;
		SCREEN_HEIGHT = r.h;
		SDL_SetWindowSize(win, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		double width_scalar = SCREEN_WIDTH / VIEWPORT_SIZE;
		double height_scalar = SCREEN_HEIGHT / VIEWPORT_SIZE;
		
		VIEWPORT_SCALAR = std::min(width_scalar, height_scalar);
	}
};
