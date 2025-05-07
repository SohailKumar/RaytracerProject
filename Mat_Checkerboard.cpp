#include "Mat_Checkerboard.h"
#include "Object.h"
#include "World.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <print>

Mat_Checkerboard::Mat_Checkerboard(glm::vec3 color1, glm::vec3 color2, float size, float ambientPercent)
{
	this->color1 = color1;
	this->color2 = color2;
	this->size = size;
	this->ambientPercent = ambientPercent;
}

glm::vec3 Mat_Checkerboard::CalculateRadiance(IntersectionData& intersectionData, World& world)
{
	glm::vec3 finalColor = glm::vec3(0.0f, 0.0f, 0.0f);

	// Use UV Coordinates to get color
	auto [u, v] = intersectionData.object->GetUVCoordinates(intersectionData);

	int urow = static_cast<int>(u / this->size);
	int vrow = static_cast<int>(v / this->size);

	bool urowOdd = (urow % 2 == 0);
	bool vrowOdd = (vrow % 2 == 0);

	if ((urowOdd && vrowOdd) || (!urowOdd && !vrowOdd))
	{
		finalColor = this->color1;
	}
	else
	{
		finalColor = this->color2;
	}

	// Check if in shadow

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
		intersectionData.reflection = world.Reflect(intersectionData.incoming * -1.0f, intersectionData.normal);
		totalDiffuse += light->color * light->intensity * finalColor * (glm::clamp(glm::dot(intersectionData.incoming, intersectionData.normal), 0.0f, 1.0f));
		totalSpecular += light->color * light->intensity * glm::vec3(1.0f,1.0f,1.0f) * std::pow(glm::clamp(glm::dot(intersectionData.reflection, intersectionData.viewDir), 0.0f, 1.0f), 1.2f);

	}
	glm::vec3 thing = glm::vec3(0.0f);
	thing += (1.0f * totalDiffuse);
	thing += (0.4f * totalSpecular);
	//std::println("totalDifffuse: {}, totalSpecular {}, finalColor: {}", totalDiffuse[0], totalSpecular[0], finalColor[0]);
	//std::println("thing: {}, {}, {}", thing[0], thing[1], thing[2]);
	return thing;
}


