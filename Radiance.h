#include <glm/glm.hpp>

#ifndef RADIANCE_H
#define RADIANCE_H

class Radiance {
public:
	Radiance(glm::vec3 values);
	glm::vec3 radianceValues;
};

#endif