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
	//loop through objects in objects array.
	//if object intersects with ray, return object
	//else return NULL
	for (const auto& obj : this->objects) {
		//std::cout << "Ray: " << glm::to_string(r.direction) << std::endl;
		/*if (r.direction[0] < 0.05 && r.direction[0] > -0.05 && r.direction[1] < 0.05 && r.direction[1] > -0.05) {
			std::cout << "Ray: " << glm::to_string(r.direction) << std::endl;
		}*/
		if (obj->Intersect(r)) {

			//std::cout << "INTERSECT";
			return obj->radiance.radianceValues;
		}

	}
	return glm::vec3(0.0f, 0.0f, 0.0f);
}