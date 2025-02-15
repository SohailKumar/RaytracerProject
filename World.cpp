#include "World.h"
#include "Ray.h"
#include "Radiance.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


World::World() {
	return;
}

void World::Add(Object& obj) {

	this->objects.push_back(obj);
}

//void World::transform(Object obj) {
//	return;
//}

void World::transformAll(glm::mat4 viewMatrix) {
	for (Object* obj : this->objects) {
		obj->Transform(viewMatrix);
	}

	return;
}

glm::vec3 World::spawn(Ray r) {
	//loop through objects in objects array.
	//if object intersects with ray, return object
	//else return NULL
	for (Object* obj : this->objects) {
		//std::cout << "Ray: " << glm::to_string(r.direction) << std::endl;
		/*if (r.direction[0] < 0.05 && r.direction[0] > -0.05 && r.direction[1] < 0.05 && r.direction[1] > -0.05) {
			std::cout << "Ray: " << glm::to_string(r.direction) << std::endl;

		}*/
		if (obj->Intersect(&r)) {

			//std::cout << "INTERSECT";
			return obj->rgb;
		}

	}
	return glm::vec3(0, 0, 0);
}