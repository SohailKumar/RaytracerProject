#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere() {
    this->center = glm::vec3(0.0f, 0.0f, 0.0f);
    this->radius = 5;
}

Sphere::Sphere(glm::vec3 center, int radius) {
    this->center = center;
    this->radius = radius;
}

bool Sphere::Intersect(Ray r) {
	//TODO: Implement this function for each obejct
	if (r.origin == this->center) {
		return true;
	}
	return false;
}

void Sphere::Transform(glm::mat3x3 transformMatrix) {
	this->center = transformMatrix * this->center;
	//TODO: Implement this function for each object
}