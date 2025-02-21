#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <optional>

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

	//TODO: make intersectiondata optional.
	bool checkRayObjectIntersect(Ray r, IntersectionData& intersectionData, Object*& retObj);
};
