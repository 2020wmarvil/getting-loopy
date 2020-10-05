#pragma once

#include "entity.h"

class Track : public Entity {
private:
public:
	Track(double x, double y, double theta, double track_length, SDL_Texture *texture, unsigned int id) { 
		this->id = id;

		this->w = track_length;
		this->h = 0.2;

		SDL_Rect clip = {
			clip.x = 0, clip.y = 0,
			clip.w = 10, clip.h = 2
		}; this->texture = { texture, clip };

		this->theta = theta;

		this->p = { x, y };

		this->computeBoundingBox();
	}
};
