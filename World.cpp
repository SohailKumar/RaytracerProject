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
		return glm::vec3(0.0f, 0.0f, 0.0f); //WORLD COLOR
	}//else it populates intersectionData variable

	primaryIntersection.object = intersectingObject;
	primaryIntersection.lights = &this->lights;
	return intersectingObject->illuminanceModel->CalculateRadiance(primaryIntersection, *this);

	//IntersectionData secondaryIntersection = {};

	////std::tuple<glm::vec3, glm::vec3> returnValues = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) };
	//glm::vec3 diffuseVariable = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 specularVariable = glm::vec3(0.0f, 0.0f, 0.0f);

	////for each light source
	//for (const auto& light : this->lights) {
	//	glm::vec3 rayToLightDir = glm::normalize(light->position - primaryIntersection.point);
	//	Ray rayToLight = Ray(primaryIntersection.point + this->EPSILON * rayToLightDir, rayToLightDir);
	//	Object* randomObject;
	//	if (CheckRayObjectIntersect(rayToLight, secondaryIntersection, randomObject)) {
	//		//currently in shadow
	//		//return glm::vec3(0.0f, 0.0f, 0.0f);
	//		continue;
	//	}
	//	primaryIntersection.incoming = rayToLightDir;
	//	primaryIntersection.reflection = Reflect(primaryIntersection.incoming, primaryIntersection.normal);

	//	//TODO: REPLACE WITH MATERIAL DATA
	//	//return intersectingObject->
	//	//std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>(Sphere(glm::vec3(-1.0f, 1.0f, -4.0f), 3, glm::vec3(0.0, 0.0, 1.0)));
	//	//intersectingObject = reinterpret_cast<std::unique_ptr<Object>*>(&sphere);
	//	auto [diffuseVariableTemp, specularVariableTemp] = intersectingObject->CalculateColor(primaryIntersection, light.get());
	//	diffuseVariable += diffuseVariableTemp;
	//	specularVariable += specularVariableTemp;

	//	//return glm::vec3(0.0f, 1.0f, 0.0f);
	//}
	//glm::vec3 finalColor = glm::vec3(0.0f, 0.0f, 0.0f);
	//finalColor += (intersectingObject->material.ambient_k * intersectingObject->material.diffuseColor * glm::vec3(0.2f, 0.2f, 0.2f));
	//finalColor += (intersectingObject->material.diffuse_k * diffuseVariable);
	//finalColor += (intersectingObject->material.specular_k * specularVariable);
	//return finalColor;
	////return returnRadiance;
	////return glm::vec3(0.0f, 0.0f, 0.0f);
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