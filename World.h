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
	static const float EPSILON;
	static const int MAX_DEPTH;
	const glm::vec3 backgroundColor;
	

	World();
	World(glm::vec3 bgColor);
	
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Light>> lights;

	void Add(std::unique_ptr<Object> obj);
	void Add(std::unique_ptr<Light> light);

	void TransformAll(glm::mat4 viewMatrix);

	glm::vec3 Spawn(Ray r, int depth);

	//TODO: make intersectiondata optional.
	bool CheckRayObjectIntersect(Ray r, IntersectionData& intersectionData, Object*& retObj);

	glm::vec3 Reflect(glm::vec3 rayToReflect, glm::vec3 normalVec);

	//glm::vec3 Refract(glm::vec3 rayIncident, glm::vec3 rayNormal, float n1, float n2);
};
