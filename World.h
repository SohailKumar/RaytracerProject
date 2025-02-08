#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include "Ray.h"

#ifndef WORLD_H
#define WORLD_H

class World {
public:
	World();
	
	std::vector<Object*> objects;

	void Add(Object* obj);
	//void transform(Object obj);
	void transformAll(glm::mat4 viewMatrix);
	Radiance* spawn(Ray r);

};

#endif