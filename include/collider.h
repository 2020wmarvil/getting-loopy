#pragma once

#include <vector>

#include "entity.h"

class Collider {
private:
	std::vector<Entity*> entities;
public:
	Collider() {}

	void addEntity(Entity *entity) { entities.push_back(entity); }

	std::vector<Entity*> collide(Entity *e1) {
		std::vector<Entity*> collided;

		for (Entity *e2 : entities) {
			if (e1->getID() == e2->getID()) continue;

			BoundingBox b1 = e1->getBoundingBox();
			BoundingBox b2 = e2->getBoundingBox();

			collided.push_back(e2);
		}

		return collided;
	}
};
