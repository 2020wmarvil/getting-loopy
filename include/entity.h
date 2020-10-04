#pragma once

struct Texture {
	SDL_Texture *texture;
	SDL_Rect clip, dst;
};

class Entity {
protected:
	double x, y;
	Texture texture;
public:
	double getX() const { return this->x; }
	double getY() const { return this->y; }

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	const Texture& getTexture() const { return this->texture; }
};
