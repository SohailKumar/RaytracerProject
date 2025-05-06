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
const int World::MAX_DEPTH = 5;

World::World() : backgroundColor(glm::vec3(0.3f, 0.5f, 0.3f)) {
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



//returns radiance at intersection
glm::vec3 World::Spawn(Ray r, int depth) {

	//should return a color
	IntersectionData primaryIntersection = {}; // this will also contain a pointer to the material 
	Object* intersectingObject;
	if (!CheckRayObjectIntersect(r, primaryIntersection, intersectingObject)) {
		return backgroundColor; //WORLD COLOR because no intersection
	}
	
	//populate intersectionData variable
	primaryIntersection.object = intersectingObject;
	primaryIntersection.lights = &this->lights;

	//glm::vec3 returnRadiance = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 returnRadiance = intersectingObject->illuminanceModel->CalculateRadiance(primaryIntersection, *this);

	if (depth < MAX_DEPTH) {
		if (intersectingObject->reflectionK > 0) {
			Ray reflectionRay = Ray(primaryIntersection.point + (EPSILON * primaryIntersection.normal), Reflect(primaryIntersection.viewDir * -1.0f, primaryIntersection.normal));
			returnRadiance += intersectingObject->reflectionK * Spawn(reflectionRay, depth + 1);
			//std::cout << "REFLECTIN";
		}
		if (intersectingObject->transmissionK > 0) {
			//primaryIntersection.incoming is facing away by default (correct)
			float checkDotProduct = glm::dot(primaryIntersection.viewDir, primaryIntersection.normal);
			float n1 = 1.0f;
			float n2 = intersectingObject->transmissionK;
			glm::vec3 incident = primaryIntersection.viewDir * -1.0f;
			glm::vec3 normal = primaryIntersection.normal;

			if (checkDotProduct < 0.0f) { //inside object
				n1 = intersectingObject->transmissionK;
				n2 = 1.0f;
				normal = primaryIntersection.normal * -1.0f;
			}

			//REFRACTION
			float n = n1 / n2;
			float cosThetaIncident = -1.0f * glm::dot(incident, normal);
			float sinSquaredThetaTransmision = n * n * (1.0f - (cosThetaIncident * cosThetaIncident));

			if (sinSquaredThetaTransmision > 1.0f) {
				//TOTAL INTERNAL REFLECTION
				Ray reflectionRay = Ray(primaryIntersection.point + (EPSILON * normal), Reflect(incident, normal));
				returnRadiance += intersectingObject->transmissionK * Spawn(reflectionRay, depth + 1);
			}
			else {


				float cosThetaTransmision = sqrt(1.0f - sinSquaredThetaTransmision);
				glm::vec3 transmissionRayDir = glm::normalize(n * incident + ((n * cosThetaIncident - cosThetaTransmision) * normal));
				Ray transmissionRay = Ray(primaryIntersection.point + (EPSILON * transmissionRayDir), transmissionRayDir);
				returnRadiance += intersectingObject->transmissionK * Spawn(transmissionRay, depth + 1);
			}
		}
	}
	
	return returnRadiance;
}

//Reflect function expects the ray to be pointing towards the origin of the normal vector that it's reflecting with respect to.
glm::vec3 World::Reflect(glm::vec3 rayToReflect, glm::vec3 normalVec) 
{
	return glm::normalize(rayToReflect - (2.0f * normalVec * (glm::dot(rayToReflect, normalVec))) );
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