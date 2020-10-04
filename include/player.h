#pragma once

#include "entity.h"

class Player : public Entity {
private:
public:
	Player(float x, float y, SDL_Texture *texture) { 
		this->x = x;
		this->y = y;

		SDL_Rect clip;
		clip.x = 0; clip.y = 0;
		clip.w = 16; clip.h = 16;
		
		SDL_Rect dst;
		dst.x = 10; dst.y = 10;
		dst.w = 20; dst.h = 20;

		this->texture = { texture, clip, dst };
	}
};
