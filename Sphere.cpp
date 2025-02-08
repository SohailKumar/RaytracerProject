#include <glm/glm.hpp>
#include "Sphere.h"
#include "Ray.h"
//#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>

Sphere::Sphere() {
    this->center = glm::vec3(0.0f, 0.0f, 0.0f);
    this->radius = 5;
	this->radiance = new Radiance(glm::vec3(1.0f, 0.0f, 0.0f));
}

Sphere::Sphere(glm::vec3 center, int radius, glm::vec3 radiance) {
    this->center = center;
    this->radius = radius;
	this->radiance = new Radiance(radiance);
}

bool Sphere::Intersect(Ray* r) {
	glm::vec3 differenceOriginCenter = r->origin - this->center;

	double a = 1;
	double b = 2.0f * glm::dot(r->direction, differenceOriginCenter);
	double c = glm::dot(differenceOriginCenter, differenceOriginCenter) - (this->radius * this->radius);

	double discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0) {
		return false;
	}

	double sqrtDiscriminant = sqrt(discriminant);
	double t1 = (-b - sqrtDiscriminant) / 2.0f;
	double t2 = (-b + sqrtDiscriminant) / 2.0f;

	if (t1 > 0) {
		return true;
	}
	if (t2 > 0) {
		return true;
	}
	return false;
}

void Sphere::Transform(glm::mat4 transformMatrix) {
	//std::cout << "TRNSFORMING" << glm::to_string(transformMatrix) << std::endl;
	//std::cout << "before " << glm::to_string(this->center) << std::endl;
	this->center = transformMatrix * glm::vec4(center, 1.0);
	//std::cout << "after " << glm::to_string(this->center) << std::endl;
}