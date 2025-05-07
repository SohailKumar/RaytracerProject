#include "Mat_AshikhminShirley.h"
#include "Object.h"
#include "World.h"
#include <iostream>

Mat_AshikhminShirley::Mat_AshikhminShirley(glm::vec3 diffuseColor, glm::vec3 specularColor, float nu, float nv)
{
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->nu = nu; 
	this->nv = nv; 
}

glm::vec3 Mat_AshikhminShirley::CalculateRadiance(IntersectionData& intersectionData, World& world)
{
	std::pair<glm::vec3, glm::vec3> tangentBitangent = intersectionData.object->GetTangentBitangent();
	glm::vec3 tangent = tangentBitangent.first;
	glm::vec3 bitangent = tangentBitangent.second;
	glm::vec3 normal = intersectionData.normal;
	glm::vec3 viewDir = intersectionData.viewDir;
	//glm::vec3 incoming = intersectionData.incoming; //towards light

	glm::vec3 totalDiffuse = glm::vec3(0.0f);
	glm::vec3 totalSpecular = glm::vec3(0.0f);

	IntersectionData secondaryIntersection = {};

	for (const auto& light : *intersectionData.lights) {
		glm::vec3 rayToLightDir = glm::normalize(light->position - intersectionData.point);
		Ray rayToLight = Ray(intersectionData.point + world.EPSILON, rayToLightDir);

		Object* tempObject; //only because intersection function requires it
		if (world.CheckRayObjectIntersect(rayToLight, secondaryIntersection, tempObject)) {
			continue;
		}

		intersectionData.incoming = rayToLightDir;

		float diffuseTerm1 = (1.0f - std::pow((1.0f - (glm::clamp(glm::dot(normal, intersectionData.incoming), 0.0f, 1.0f)) / 2), 5));
		float diffuseTerm2 = (1.0f - std::pow((1.0f - (glm::clamp(glm::dot(normal, intersectionData.viewDir), 0.0f, 1.0f)) / 2), 5));
		totalDiffuse += light->color * light->intensity * 28.0f / 23.0f * diffuseColor / (3.14f) * (1.0f - specularColor) * diffuseTerm1 * diffuseTerm2;

		
		glm::vec3 halfVector = glm::normalize(intersectionData.incoming + intersectionData.viewDir);
		float hn = glm::clamp(glm::dot(halfVector, normal), 0.0f, 1.0f);
		float hu = glm::clamp(glm::dot(halfVector, tangent), 0.0f, 1.0f);
		float hv = glm::clamp(glm::dot(halfVector, bitangent), 0.0f, 1.0f);
		float hk2 = glm::clamp(glm::dot(halfVector, viewDir), 0.0f, 1.0f);
		float nk1  = glm::clamp(glm::dot(normal, intersectionData.incoming), 0.0f, 1.0f);
		float nk2 = glm::clamp(glm::dot(normal, viewDir), 0.0f, 1.0f);

		float specularTerm1 = std::sqrt((this->nu + 1.0f) * (this->nv + 1.0f)) / 8.0f / (3.14f);
		float exponent = (this->nu * std::pow(hu, 2) + this->nv * std::pow(hv, 2)) / (1.0f - std::pow(hn, 2));
		float specularTerm2 = std::pow(hn, exponent) / (hk2 * std::max(nk1, nk2));
		glm::vec3 fresnelTerm = this->specularColor + (glm::vec3(1.0f,1.0f,1.0f) - this->specularColor);
		totalSpecular += light->color * light->intensity * specularTerm1 * specularTerm2 * fresnelTerm;

	}
	glm::vec3 finalColor = glm::vec3(0.0f);
	finalColor += (1.0f * totalDiffuse);
	finalColor += (0.8f * totalSpecular);
	return finalColor;



    return glm::vec3();
}
