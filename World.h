#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <optional>

class Object;

#include "Object.h"
#include "Ray.h"
#include "Light.h"

class World {
public:

	static const float epsilon;

	World();
	
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Light>> lights;

	void Add(std::unique_ptr<Object> obj);
	void Add(std::unique_ptr<Light> light);

	void TransformAll(glm::mat4 viewMatrix);

	glm::vec3 Spawn(Ray r);

	//TODO: make intersectiondata optional.
	bool CheckRayObjectIntersect(Ray r, IntersectionData& intersectionData, Object*& retObj);

	glm::vec3 Reflect(glm::vec3 rayToReflect, glm::vec3 normalVec);
};
