#include "Mat_ImageTexture.h"
#include "Object.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Mat_ImageTexture::Mat_ImageTexture(std::string filepath)
{
	this->filepath = filepath;
	this->data = stbi_load(this->filepath.c_str(), &this->width, &this->height, &this->channels, 0);
	if (!data) {
		std::cout << "bad";
	}
}

glm::vec3 Mat_ImageTexture::CalculateRadiance(IntersectionData& intersectionData, World& world)
{
	auto [u, v] = intersectionData.object->GetUVCoordinates(intersectionData);

	int x = int(u * this->width);
	int y = int((1-v) * this->height);
	int index = (y * this->width + x) * this->channels;
	unsigned char r = this->data[index];
	unsigned char g = this->data[index + 1];
	unsigned char b = this->data[index + 2];
	glm::vec3 finalColor = glm::vec3(r, g, b) / 255.0f;
	

	return finalColor;
}

void Mat_ImageTexture::FreeImage() {

	stbi_image_free(this->data);
}
