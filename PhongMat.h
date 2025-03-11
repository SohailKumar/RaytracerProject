#pragma once

#include "IlluminanceModel.h"

class PhongMat : IlluminanceModel {
public:
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float ambient_k;
	float diffuse_k;
	float specular_k;
	float shiny_exp;

	PhongMat();
	PhongMat(glm::vec3 diffuseColor, glm::vec3 specularColor, float ambient_k, float diffuse_k, float specular_k, float shiny_exp);

	glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world);
};