#include "Light.h"

Light::Light() {
	this->position = glm::vec3(0.0f, 10.0f, 3.0f);
	this->color = glm::vec3(0.0f, 1.0f, 0.0f);
}

Light::Light(glm::vec3 position, glm::vec3 color) {
	this->position = position;
	this->color = color;
}