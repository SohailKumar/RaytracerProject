#include <glm/glm.hpp>

#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
	Material();
	Material(glm::vec3 values);
	glm::vec3 radianceValues;
};

#endif