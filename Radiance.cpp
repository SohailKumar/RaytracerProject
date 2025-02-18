#include "Radiance.h"

Radiance::Radiance() {
	this->radianceValues = glm::vec3(0.0f, 0.0f, 0.0f);
}

Radiance::Radiance(glm::vec3 values) {
	this->radianceValues = values;
}