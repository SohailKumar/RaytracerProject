
#include <glm/glm.hpp>

#include "PhongMat.h"
#include "Ray.h"
#include "World.h"

PhongMat::PhongMat() {
	diffuseColor = glm::vec3(1.0, 0.0, 0.0); //r=0, g=1, b=0
	specularColor = glm::vec3(1.0f, 1.0f, 1.0f); //r=1, g=0, b=0
	ambient_k = 1.0f;
	diffuse_k = 1.0f;
	specular_k = 0.9f;
	shiny_exp = 2.0f;
}

PhongMat::PhongMat(glm::vec3 diffuseColor, glm::vec3 specularColor, float ambient_k, float diffuse_k, float specular_k, float shiny_exp) {
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->ambient_k = ambient_k;
	this->diffuse_k = diffuse_k;
	this->specular_k = specular_k;
	this->shiny_exp = shiny_exp;
}

glm::vec3 PhongMat::CalculateRadiance(IntersectionData& intersectionData, World& world)
{
	IntersectionData secondaryIntersection = {};
	glm::vec3 diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 specular = glm::vec3(0.0f, 0.0f, 0.0f);

	for (const auto& light : *intersectionData.lights) {
        glm::vec3 rayToLightDir = glm::normalize(light->position - intersectionData.point);
		Ray rayToLight = Ray(intersectionData.point + World::epsilon * rayToLightDir, rayToLightDir);

		//check if this light intersects with any objects in its path.
		Object* randomObject;
		if (world.CheckRayObjectIntersect(rayToLight, secondaryIntersection, randomObject)) {
			//currently in shadow for this light
			continue;
		}

		intersectionData.incoming = rayToLightDir;
		intersectionData.reflection = world.Reflect(intersectionData.incoming, intersectionData.normal);

		diffuse += light->color * this->diffuseColor * (glm::clamp(glm::dot(intersectionData.incoming, intersectionData.normal), 0.0f, 1.0f));
		specular += light->color * this->specularColor * std::pow(glm::clamp(glm::dot((intersectionData.reflection), intersectionData.viewDir), 0.0f, 1.0f), shiny_exp);
	}

	glm::vec3 finalColor = glm::vec3(0.0f, 0.0f, 0.0f);
	finalColor += (this->ambient_k * this->diffuseColor * glm::vec3(0.2f, 0.2f, 0.2f)); //TODO get rid of this random vec3
	finalColor += (this->diffuse_k * diffuse);
	finalColor += (this->specular_k * specular);
	return finalColor;
}
