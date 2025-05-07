#include "Mat_PhongBlinn.h"
#include "Ray.h"
#include "World.h" 
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Mat_PhongBlinn::Mat_PhongBlinn(glm::vec3 diffuseColor, glm::vec3 specularColor, float ambient_k, float diffuse_k, float specular_k, float shiny_exp)
{
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->ambient_k = ambient_k;
	this->diffuse_k = diffuse_k;
	this->specular_k = specular_k;
	this->shiny_exp = shiny_exp;
}

glm::vec3 Mat_PhongBlinn::CalculateRadiance(IntersectionData& intersectionData, World& world)
{
	glm::vec3 totalDiffuse = glm::vec3(0.0f);
	glm::vec3 totalSpecular = glm::vec3(0.0f);

	IntersectionData secondaryIntersection = {};

	for (const auto& light : *intersectionData.lights) {
		glm::vec3 rayToLightDir = glm::normalize(light->position - intersectionData.point);
		Ray rayToLight = Ray(intersectionData.point + intersectionData.normal * world.EPSILON, rayToLightDir);

		Object* tempObject; //only because intersection function requires it
		if (world.CheckRayObjectIntersect(rayToLight, secondaryIntersection, tempObject)) {
			continue;
		}

		intersectionData.incoming = rayToLightDir;
		intersectionData.reflection = world.Reflect(intersectionData.incoming * -1.0f, intersectionData.normal);

		glm::vec3 halfVector = glm::normalize(intersectionData.incoming + intersectionData.viewDir);

		totalDiffuse += light->color * light->intensity * this->diffuseColor * (glm::clamp(glm::dot(intersectionData.incoming, intersectionData.normal), 0.0f, 1.0f));
		totalSpecular += light->color * light->intensity * this->specularColor * std::pow(glm::clamp(glm::dot(halfVector, intersectionData.normal), 0.0f, 1.0f), shiny_exp);
	}

	glm::vec3 finalColor = glm::vec3(0.0f, 0.0f, 0.0f);
	finalColor += (this->diffuse_k * totalDiffuse);
	finalColor += (this->specular_k * totalSpecular);
	return finalColor;
}
