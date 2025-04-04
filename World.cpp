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

const float World::EPSILON = 0.01f;

World::World() : backgroundColor(glm::vec3(0.0f, 0.0f, 0.0f)) {
	return;
}

World::World(glm::vec3 bgColor) : backgroundColor(bgColor){
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

	for (auto& light : this->lights) {
		light->Transform(viewMatrix);
	}

	return;
}

glm::vec3 World::Spawn(Ray r) {

	//should return a color
	IntersectionData primaryIntersection = {}; // this will also contain a pointer to the material 
	Object* intersectingObject;
	if (!CheckRayObjectIntersect(r, primaryIntersection, intersectingObject)) {
		return backgroundColor; //WORLD COLOR because no intersection
	}
	
	//populate intersectionData variable
	primaryIntersection.object = intersectingObject;
	primaryIntersection.lights = &this->lights;

	return intersectingObject->illuminanceModel->CalculateRadiance(primaryIntersection, *this);
}

glm::vec3 World::Reflect(glm::vec3 rayToReflect, glm::vec3 normalVec) 
{
	return glm::normalize((2.0f * normalVec * (glm::dot(rayToReflect, normalVec))) - rayToReflect );
}

bool World::CheckRayObjectIntersect(Ray r, IntersectionData& intersectionData, Object*& retObj)  //TODO make object optional.
{
	for (const auto& obj : this->objects) {
		if (obj->Intersect(r, intersectionData)) {
			retObj = obj.get();
			return true;
		}
	}
	return false;
}