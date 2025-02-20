#include "Material.h"

Material::Material() {
	this->radianceValues = glm::vec3(0.0f, 0.0f, 0.0f);
}

Material::Material(glm::vec3 values) {
	this->radianceValues = values;
}