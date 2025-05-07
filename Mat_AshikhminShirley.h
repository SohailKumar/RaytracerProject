#pragma once

#include <glm/glm.hpp>

#include "IlluminanceModel.h"


class Mat_AshikhminShirley : public IlluminanceModel {
public:
	Mat_AshikhminShirley(glm::vec3 diffuseColor, glm::vec3 specularColor, float nu, float nv);

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float nu; // Roughness exponent in the tangent direction
	float nv; // Roughness exponent in the bitangent direction

	glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world);
};