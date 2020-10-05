#pragma once

#include "entity.h"

class Player : public Entity {
private:
public:
	Player(float x, float y, SDL_Texture *texture) { 
		this->x = x;
		this->y = y;
		this->w = 10;
		this->h = 10;

		SDL_Rect clip;
		clip.x = 0; clip.y = 0;
		clip.w = 16; clip.h = 16;

		this->texture = { texture, clip };
	}
};
