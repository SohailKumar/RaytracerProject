#pragma once

#include <glm/glm.hpp>
#include <tuple>


#include "Light.h"
#include "IntersectionData.h"
class World;

class IlluminanceModel {
public:
	//Material(glm::vec3 values, glm::vec3 diffuseColor, glm::vec3 specularColor, float ambient_k, float diffuse_k, float specular_k, float shiny_exp);
	IntersectionData intersectionData;

	virtual glm::vec3 CalculateRadiance(IntersectionData& intersectionData, World& world) = 0;

};