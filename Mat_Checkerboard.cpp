#include "Mat_Checkerboard.h"
#include "Object.h"
#include "World.h"

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

	glm::vec3 diffuseColor = glm::vec3(0.0f, 0.0f, 0.0f);
	if ((urowOdd && vrowOdd) || (!urowOdd && !vrowOdd))
	{
		diffuseColor = this->color1;
	}
	else
	{
		diffuseColor = this->color2;
	}

	// Check if in shadow
	glm::vec3 totalDiffuse = glm::vec3(0.0f);

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
		totalDiffuse += light->color * diffuseColor * (glm::clamp(glm::dot(intersectionData.incoming, intersectionData.normal), 0.0f, 1.0f));
	}

	return totalDiffuse * 2.0f;
}


