#pragma once

#define VIEWPORT_SIZE 100

#include "entity.h"

class Renderer {
private:
	int SCREEN_WIDTH, SCREEN_HEIGHT, VIEWPORT_SCALAR;
	int x_offset=0, y_offset=0;

	SDL_Renderer *renderer;

	SDL_Texture *ground_texture=nullptr;
public:
	Renderer(SDL_Renderer* renderer, SDL_Window* window) : renderer(renderer) {
		updateDisplay(window);
	}

	void render(const Entity& entity) {
		Texture texture = entity.getTexture();

		SDL_Rect dst;
		dst.x = entity.getX() * VIEWPORT_SCALAR + x_offset; 
		dst.y = entity.getY() * VIEWPORT_SCALAR + y_offset;
		dst.w = entity.getWidth() * VIEWPORT_SCALAR; 
		dst.h = entity.getHeight() * VIEWPORT_SCALAR;

		dst.y = SCREEN_HEIGHT - dst.y - dst.h;
	
        	SDL_RenderCopy(this->renderer, texture.texture, &texture.clip, &dst);
	}

	void renderGround() {
		if (ground_texture == nullptr) return;

		int thickness = SCREEN_HEIGHT / 5;

		y_offset = thickness / 2;

		SDL_Rect dst;
		dst.x = -SCREEN_WIDTH / 2; 
		dst.y = SCREEN_HEIGHT - thickness / 2;
		dst.w = SCREEN_WIDTH * 2; 
		dst.h = thickness; 
	
        	SDL_RenderCopy(this->renderer, this->ground_texture, NULL, &dst);
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

	void setGroundTexture(const std::string& file) {
		this->ground_texture = loadTexture(file);
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

		x_offset = (SCREEN_WIDTH - VIEWPORT_SIZE) / 2;
		y_offset = (SCREEN_HEIGHT - VIEWPORT_SIZE) / 2;
	}
};
