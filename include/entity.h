#pragma once

struct Texture {
	SDL_Texture *texture;
	SDL_Rect clip;
};

struct Position { double x; double y; };
struct BoundingBox { double x1; double x2; double y1; double y2; };

class Entity {
protected:
	double w, h;
	Texture texture;

	Position p;
	BoundingBox bb;
public:
	double getWidth() const { return this->w; }
	double getHeight() const { return this->h; }
	const Texture& getTexture() const { return this->texture; }

	double getX() const { return this->p.x; }
	double getY() const { return this->p.y; }
};
