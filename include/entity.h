#pragma once

struct Texture {
	SDL_Texture *texture;
	SDL_Rect clip;
};

struct Position { double x; double y; };

struct Point { double x; double y; };
struct BoundingBox { 
	Point UL; Point UR;
	Point LL; Point LR;
};

class Entity {
protected:
	unsigned int id;

	double w, h;
	Texture texture;

	double theta; // stored in radians

	Position p;
	BoundingBox bounding_box;

	void computeBoundingBox() {
		double UL_x = p.x - w / 2; 
		double UL_y = p.y + h / 2;

		double UR_x = p.x + w / 2;
		double UR_y = p.y + h / 2;

		double LL_x = p.x - w / 2;
		double LL_y = p.y - h / 2;

		double LR_x = p.x + w / 2;
		double LR_y = p.y - h / 2;

		this->bounding_box = { 
			{ 
				p.x + (UL_x - p.x)*cos(theta) + (UL_y - p.y)*sin(theta),
				p.y - (UL_x - p.x)*sin(theta) + (UL_y - p.y)*cos(theta)
			},
			{ 
				p.x + (UR_x - p.x)*cos(theta) + (UR_y - p.y)*sin(theta),
				p.y - (UR_x - p.x)*sin(theta) + (UR_y - p.y)*cos(theta)
			},
			{ 
				p.x + (LL_x - p.x)*cos(theta) + (LL_y - p.y)*sin(theta),
				p.y - (LL_x - p.x)*sin(theta) + (LL_y - p.y)*cos(theta)
			},
			{ 
				p.x + (LR_x - p.x)*cos(theta) + (LR_y - p.y)*sin(theta),
				p.y - (LR_x - p.x)*sin(theta) + (LR_y - p.y)*cos(theta)
			},
		};
	}
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
