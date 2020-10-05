#pragma once

#include <vector>

#include "entity.h"
#include "collider.h"

struct Velocity { double x; double y; };
struct Acceleration { double x; double y; };

class PhysicsEntity : public Entity {
protected:
	Velocity v;
	Acceleration a;
public:
	void setVelocityX(double x) { this->v.x = x; }
	void setVelocityY(double y) { this->v.y = y; }

	bool update(double dt, const std::vector<Collision*>& collided) {
		double ground_level = 0.0;
		if (p.y <= ground_level) {
			p.y = ground_level;
			return false;
		}

		p.x += (v.x + dt * a.x / 2) * dt;
		p.y += (v.y + dt * a.y / 2) * dt;

		v.x += a.x * dt;
		v.y += a.y * dt;

	//	std::cout << "Variables:\n";
	//	std::cout << "\tv: (" << v.x << ", " << v.y << ")\n";
	//	std::cout << "\tp: (" << p.x << ", " << p.y << ")\n";
	
		this->computeBoundingBox();

		return true;
	}
};
