#pragma once

struct Texture {
	SDL_Texture *texture;
	SDL_Rect clip;
};

class Entity {
protected:
	double x, y;
	int w, h;
	Texture texture;
public:
	double getX() const { return this->x; }
	double getY() const { return this->y; }
	double getWidth() const { return this->w; }
	double getHeight() const { return this->h; }

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	const Texture& getTexture() const { return this->texture; }
};
