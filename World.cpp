#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "World.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"


World::World() {
	return;
}

void World::Add(std::unique_ptr<Object> obj) {
	this->objects.push_back(std::move(obj));
}

void World::Add(std::unique_ptr<Light> light) {
	this->lights.push_back(std::move(light));
}

void World::transformAll(glm::mat4 viewMatrix) {
	for (auto& obj : this->objects) {
		obj->Transform(viewMatrix);
	}

	return;
}

glm::vec3 World::spawn(Ray r) {
	//should return a color
	IntersectionData intersectionData = {};
	if (!checkRayObjectIntersect(r, intersectionData)) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}//else it populates intersectionData variable

	IntersectionData secondaryIntersection = {};

	for (const auto& light : this->lights) {
		Ray rayToLight = Ray(intersectionData.point, glm::normalize(light->position - intersectionData.point));

		if (checkRayObjectIntersect(rayToLight, secondaryIntersection)) {
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}
		return glm::vec3(1.0f, 0.0f, 0.0f); //TODO: REPLACE WITH MATERIAL DATA
	}
}

bool World::checkRayObjectIntersect(Ray r, IntersectionData& intersectionData) {
	for (const auto& obj : this->objects) {
		if (obj->Intersect(r, intersectionData)) {
			return true;
		}
	}
	return false;
}