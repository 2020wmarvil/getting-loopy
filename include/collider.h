#pragma once

#include <vector>

#include "entity.h"

struct Axis {
	double x; double y;
};

struct Collision {
	Entity *entity;
	double nx; double ny;
};

class Collider {
private:
	std::vector<Entity*> entities;

	bool SeparateAxisTheorem(BoundingBox b1, BoundingBox b2) {
		std::vector<Axis> axes;
		Axis axis1 = {
			b1.UR.x - b1.UL.x,
		       	b1.UR.y - b1.UL.y 
		}; axes.push_back(axis1);

		Axis axis2 = {
			b1.UR.x - b1.LR.x,
			b1.UR.y - b1.LR.y 
		}; axes.push_back(axis2);
		
		Axis axis3 = {
			b2.UL.x - b2.LL.x, 
			b2.UL.y - b2.LL.y 
		}; axes.push_back(axis3);
		 
		Axis axis4 = {
			b2.UL.x - b2.UR.x,
		       	b2.UL.y - b2.UR.y
		}; axes.push_back(axis4);

		for (Axis axis : axes) {
			double magnitude = std::abs(axis.x * axis.x + axis.y * axis.y);

			double proj_const = (b1.UL.x * axis.x + b1.UL.y * axis.y) / magnitude;
 			double b1_max = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			double b1_min = b1_max;

			proj_const = (b1.UR.x * axis.x + b1.UR.y * axis.y) / magnitude;
			double temp = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			if (temp > b1_max) b1_max = temp;
			if (temp < b1_min) b1_min = temp;

			proj_const = (b1.LL.x * axis.x + b1.LL.y * axis.y) / magnitude;
			temp = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			if (temp > b1_max) b1_max = temp;
			if (temp < b1_min) b1_min = temp;

			proj_const = (b1.LR.x * axis.x + b1.LR.y * axis.y) / magnitude;
			temp = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			if (temp > b1_max) b1_max = temp;
			if (temp < b1_min) b1_min = temp;

			proj_const = (b2.UL.x * axis.x + b2.UL.y * axis.y) / magnitude;
			double b2_max = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			double b2_min = b2_max;

			proj_const = (b2.UR.x * axis.x + b2.UR.y * axis.y) / magnitude;
			temp = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			if (temp > b2_max) b2_max = temp;
			if (temp < b2_min) b2_min = temp;

			proj_const = (b2.LL.x * axis.x + b2.LL.y * axis.y) / magnitude;
			temp = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			if (temp > b2_max) b2_max = temp;
			if (temp < b2_min) b2_min = temp;

			proj_const = (b2.LR.x * axis.x + b2.LR.y * axis.y) / magnitude;
			temp = proj_const * axis.x * axis.x + proj_const * axis.y * axis.y;
			if (temp > b2_max) b2_max = temp;
			if (temp < b2_min) b2_min = temp;

			if (!(b2_min <= b1_max && b2_max >= b1_min)) return false;
		}

		return true;
	}
public:
	Collider() {}

	void addEntity(Entity *entity) { 
		for (Entity *e : entities) {
			if (e->getID() == entity->getID()) return;
		} entities.push_back(entity); 
	}

	std::vector<Collision*> collide(Entity *e1) {
		std::vector<Collision*> collided;

		for (Entity *e2 : entities) {
			if (e1->getID() == e2->getID()) continue;

			if (SeparateAxisTheorem(e1->getBoundingBox(), e2->getBoundingBox())) {
				Collision col = { e2, e1->getX() - e2->getX(), e1->getY() - e2->getY() };
				collided.push_back(&col);
			}
		}

		return collided;
	}
};
