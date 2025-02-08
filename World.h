#include <glm/glm.hpp>
#include <vector>
#include "Object.h"

#ifndef WORLD_H
#define WORLD_H

class World {
public:
	World();
	
	std::vector<Object*> objects;

	void Add(Object* obj);
	//void transform(Object obj);
	void transformAll();
	Object* spawn(Ray r);

};

#endif