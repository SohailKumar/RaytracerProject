#pragma once

#include <glm/glm.hpp>

#include "IntersectionData.h"
class World;

class IlluminanceModel {
public:
	IntersectionData intersectionData;

	virtual glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world) = 0;

};