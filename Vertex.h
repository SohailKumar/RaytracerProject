#pragma once

#include <glm/glm.hpp>

class Vertex {
public:
	glm::vec3 position;
	float u, v;

	Vertex(glm::vec3 position, float u, float v) {
		this->position = position;
		this->u = u;
		this->v = v;
	}
};