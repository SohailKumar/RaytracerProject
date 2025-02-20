#pragma once
#include <glm/glm.hpp>

class Material {
public:
	Material();
	Material(glm::vec3 values);
	glm::vec3 radianceValues;
};
