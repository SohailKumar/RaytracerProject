#pragma once

#include <glm/glm.hpp>

#include "IlluminanceModel.h"


class Mat_Checkerboard : public IlluminanceModel {
public:
	Mat_Checkerboard(glm::vec3 color1, glm::vec3 color2, float size, float ambientPercent);

	glm::vec3 color1;
	glm::vec3 color2;
	float size;
	float ambientPercent;

	glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world);
};
