#include "Plane.h"
#include "Ray.h"

Plane::Plane() {
	this->planeEquation = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

}

Plane::Plane(glm::vec4 equation) {
	this->planeEquation = equation;
}

Plane::Plane(glm::vec3 normalVector, glm::vec3 center) {
	this->planeEquation = glm::vec4(normalVector[0], normalVector[1], normalVector[2], -1 * (normalVector[0] * center[0] + normalVector[1] * center[1] + normalVector[2] * center[2]));
}

bool Plane::Intersect(Ray r) {
	//TODO: Implement this function for each obejct
	return false;
}

void Plane::Transform(glm::mat3x3 transformMatrix) {
	this->center = transformMatrix * this->center;
}