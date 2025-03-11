#pragma once
#include <glm/glm.hpp>

class Light {
public:
	Light();
	Light(glm::vec3 position, glm::vec3 color);
	glm::vec3 position;
	glm::vec3 color; // in RGB 0-1

	void Transform(glm::mat4 viewMatrix);
};
