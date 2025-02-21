#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Object.h"
#include "Ray.h"
#include "Light.h"

class World {
public:
	World();
	
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Light>> lights;

	void Add(std::unique_ptr<Object> obj);
	void Add(std::unique_ptr<Light> light);

	void transformAll(glm::mat4 viewMatrix);

	glm::vec3 spawn(Ray r);
	bool checkRayObjectIntersect(Ray r, IntersectionData& intersectionData);
};
