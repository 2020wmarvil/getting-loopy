#pragma once

#include "physics_entity.h"

class Player : public PhysicsEntity {
private:
public:
	Player(double x, double y, double theta, SDL_Texture *texture, unsigned int id) { 
		this->id = id;

		this->w = 1;
		this->h = 1;

		SDL_Rect clip {
			clip.x = 0, clip.y = 0,
			clip.w = 16, clip.h = 16
		}; this->texture = { texture, clip };

		this->theta = theta;

		this->p = { x, y };
		this->v = { 0.0, 0.0 };
		this->a = { 0.0, 0.0 };

		this->bounding_box = { x - w / 2, y - h / 2, x + w / 2, y + h / 2 };
	}
};
