#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Object.h"
#include "Ray.h"

#ifndef WORLD_H
#define WORLD_H

class World {
public:
	World();
	
	std::vector<std::unique_ptr<Object>> objects;

	void Add(std::unique_ptr<Object> obj);
	//void transform(Object obj);
	void transformAll(glm::mat4 viewMatrix);
	glm::vec3 spawn(Ray r);

};

#endif