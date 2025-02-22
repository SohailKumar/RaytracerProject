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

void World::TransformAll(glm::mat4 viewMatrix) {
	for (auto& obj : this->objects) {
		obj->Transform(viewMatrix);
	}

	return;
}

glm::vec3 World::Spawn(Ray r) {
	float epsilon = 0.01;

	//should return a color
	IntersectionData primaryIntersection = {}; // this will also contain a pointer to the material 
	Object* intersectingObject;
	if (!CheckRayObjectIntersect(r, primaryIntersection, intersectingObject)) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}//else it populates intersectionData variable

	IntersectionData secondaryIntersection = {};

	//std::tuple<glm::vec3, glm::vec3> returnValues = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 diffuseVariable = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 specularVariable = glm::vec3(0.0f, 0.0f, 0.0f);

	for (const auto& light : this->lights) {
		if (primaryIntersection.point[2] > 6.5f && primaryIntersection.point[2] < 7.5f && primaryIntersection.point[1] > 3.0f && primaryIntersection.point[1] < 3.4f) {
			std::println("check {}, {}, {}", primaryIntersection.point[0], primaryIntersection.point[1], primaryIntersection.point[2]);
		}
		glm::vec3 rayToLightDir = glm::normalize(light->position - primaryIntersection.point);
		Ray rayToLight = Ray(primaryIntersection.point + epsilon * rayToLightDir, rayToLightDir);
		Object* randomObject;
		if (CheckRayObjectIntersect(rayToLight, secondaryIntersection, randomObject)) {
			//currently in shadow
			//return glm::vec3(0.0f, 0.0f, 0.0f);
			continue;
		}
		primaryIntersection.incoming = rayToLightDir * -1.0f;
		primaryIntersection.reflection = Reflect(primaryIntersection.point, primaryIntersection.incoming, primaryIntersection.normal);

		//TODO: REPLACE WITH MATERIAL DATA
		//return intersectingObject->
		//std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Sphere(glm::vec3(-1.0f, 1.0f, -4.0f), 3, glm::vec3(0.0, 0.0, 1.0)));
		//intersectingObject = reinterpret_cast<std::unique_ptr<Object>*>(&sphere);
		auto [diffuseVariableTemp, specularVariableTemp] = intersectingObject->CalculateColor(primaryIntersection, light.get());
		diffuseVariable += diffuseVariableTemp;
		specularVariable += specularVariableTemp;

		//return glm::vec3(0.0f, 1.0f, 0.0f);
	}
	return (intersectingObject->material.ambient_k * intersectingObject->material.diffuseColor* glm::vec3(0.2f, 0.2f, 0.2f)) + (intersectingObject->material.diffuse_k * diffuseVariable) + (intersectingObject->material.specular_k * specularVariable);
	//return returnRadiance;
	//return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 World::Reflect(glm::vec3 point, glm::vec3 rayToReflect, glm::vec3 normalVec) 
{
	return glm::normalize((rayToReflect - (2.0f * normalVec * (glm::dot(rayToReflect, normalVec)))));
}

bool World::CheckRayObjectIntersect(Ray r, IntersectionData& intersectionData, Object*& retObj) 
{
	for (const auto& obj : this->objects) {
		if (obj->Intersect(r, intersectionData)) {
			retObj = obj.get();
			return true;
		}
	}
	return false;
}