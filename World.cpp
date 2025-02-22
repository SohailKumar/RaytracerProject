#include <iostream>
#include <optional>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <print>

#include "World.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"

#include "Sphere.h"
#include <memory>


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
	IntersectionData primaryIntersection = {}; // this will also contain a pointer to the material 
	Object* intersectingObject;
	if (!checkRayObjectIntersect(r, primaryIntersection, intersectingObject)) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}//else it populates intersectionData variable

	IntersectionData secondaryIntersection = {};

	for (const auto& light : this->lights) {
		if (primaryIntersection.point[2] > 6.5f && primaryIntersection.point[2] < 7.5f && primaryIntersection.point[1] > 3.0f && primaryIntersection.point[1] < 3.4f) {
			std::println("check {}, {}, {}", primaryIntersection.point[0], primaryIntersection.point[1], primaryIntersection.point[2]);
		}
		Ray rayToLight = Ray(primaryIntersection.point, glm::normalize(light->position - primaryIntersection.point));
		Object* randomObject;
		if (checkRayObjectIntersect(rayToLight, secondaryIntersection, randomObject)) {
			//std::println("yes intersect");
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}
		//TODO: REPLACE WITH MATERIAL DATA
		//return intersectingObject->
		//std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Sphere(glm::vec3(-1.0f, 1.0f, -4.0f), 3, glm::vec3(0.0, 0.0, 1.0)));
		//intersectingObject = reinterpret_cast<std::unique_ptr<Object>*>(&sphere);
		return intersectingObject->CalculateColor(primaryIntersection, &this->lights);
		//return glm::vec3(0.0f, 1.0f, 0.0f);
	}
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

bool World::checkRayObjectIntersect(Ray r, IntersectionData& intersectionData, Object*& retObj) {
	for (const auto& obj : this->objects) {
		if (obj->Intersect(r, intersectionData)) {
			retObj = obj.get();
			return true;
		}
	}
	return false;
}