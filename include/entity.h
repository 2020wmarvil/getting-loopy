#pragma once

struct Texture {
	SDL_Texture *texture;
	SDL_Rect clip;
};

struct Position { double x; double y; };
struct BoundingBox { double x1; double x2; double y1; double y2; };

class Entity {
protected:
	unsigned int id;

	double w, h;
	Texture texture;

	double theta; // stored in radians

	Position p;
	BoundingBox bounding_box;
public:
	unsigned int getID() const { return this->id; }

	double getWidth() const { return this->w; }
	double getHeight() const { return this->h; }
	const Texture& getTexture() const { return this->texture; }

	double getX() const { return this->p.x; }
	double getY() const { return this->p.y; }
	double getThetaRadians() const { return this->theta; }
	double getThetaDegrees() const { return this->theta * 180 / M_PI; }

	const BoundingBox& getBoundingBox() const { return this->bounding_box; };
};
