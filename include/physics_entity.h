#pragma once

#include <vector>

#include "entity.h"
#include "collider.h"

struct Velocity { double x; double y; };
struct Acceleration { double x; double y; };
struct Force { double x; double y; };

class PhysicsEntity : public Entity {
protected:
	double m;

	Velocity v;
	Acceleration a;
	Force f;
public:
	void setVelocityX(double x) { this->v.x = x; }
	void setVelocityY(double y) { this->v.y = y; }

	bool update(double dt, const std::vector<Collision*>& collisions) {
		double ground_level = 0.0;
		if (p.y <= ground_level) {
			p.y = ground_level;
			return false;
		}

		Force Fg = { 0.0, 9.8 * m };
		Force Fn_net = { 0.0, 0.0 };

		if (collisions.size() > 0) {
			v.y = 0;
		}

		for (Collision *collision : collisions) {
			double nx = collision->nx;
			double ny = collision->ny;

			double theta = atan(ny / nx);

			double Fn_val = 1 / (cos(theta)*cos(theta) + sin(theta)*sin(theta));

			Force Fn = { Fn_val * cos(theta), Fn_val * sin(theta) };
			std::cout << "\tFn: " << Fn.x << " " << Fn.y << "\n";

			Fn_net.x += Fn.x;
			Fn_net.y += Fn.y;
		}

		if (Fn_net.x == 0) {
			this->theta = 0;
		} else {
			this->theta = atan(Fn_net.y / Fn_net.x);
		}

		Force F_net = { Fn_net.x - Fg.x, Fn_net.y - Fg.y };
		std::cout << F_net.x << " " << F_net.y << "\n";
		std::cout << "\tFg:     " << Fg.x << " " << Fg.y << "\n";
		std::cout << "\tFn_net: " << Fn_net.x << " " << Fn_net.y << "\n";

		a.x = F_net.x / m;
		a.y = F_net.y / m;

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
