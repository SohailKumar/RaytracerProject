#pragma once
#include <glm/glm.hpp>

class ToneReproducer {
public:
	float Ldmax = 100.0f; // Maximum display luminance (for your display)
	virtual glm::vec3 CalculateFinalRGB() = 0;

};