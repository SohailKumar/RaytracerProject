#pragma once

#include <glm/glm.hpp>

#include "Material.h"

class Mat_Phong : public Material {
public:
	glm::vec3 CalculateRadiance();
};
