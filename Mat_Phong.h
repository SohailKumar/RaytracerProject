#pragma once

#include <glm/glm.hpp>

#include "IlluminanceModel.h"


class Mat_Phong : public IlluminanceModel {
public:
	Mat_Phong(glm::vec3 diffuseColor, glm::vec3 specularColor, float ambient_k, float diffuse_k, float specular_k, float shiny_exp);

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float ambient_k;
	float diffuse_k;
	float specular_k;
	float shiny_exp;

	glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world);
};
