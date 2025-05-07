#pragma once
#pragma once

#include <glm/glm.hpp>

#include "IlluminanceModel.h"
#include <string>


class Mat_ImageTexture : public IlluminanceModel {
public:
	std::string filepath;
	unsigned char* data;
	int width, height, channels;
	Mat_ImageTexture(std::string filepath);


	glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world);
	void FreeImage();
};
