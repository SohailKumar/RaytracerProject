#include <glm/glm.hpp>
#include "Sphere.h"
#include "Ray.h"
#include "PhongMat.h"
//#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>


Sphere::Sphere(glm::vec3 center, double radius, Material mat)
{
	this->center = center;
	this->radius = radius;
	this->material = mat;
	this->illuminanceModel = std::make_unique<IlluminanceModel>(PhongMat(mat.diffuseColor, mat.specularColor, mat.ambient_k, mat.diffuse_k, mat.specular_k, mat.shiny_exp));
}

bool Sphere::Intersect(Ray& r, IntersectionData& intersectionData) const {
	glm::vec3 differenceOriginCenter = r.origin - this->center;

	double a = 1;
	double b = 2.0f * glm::dot(r.direction, differenceOriginCenter);
	double c = glm::dot(differenceOriginCenter, differenceOriginCenter) - (this->radius * this->radius);

	double discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0) {
		return false;
	}

	double sqrtDiscriminant = sqrt(discriminant);
	double t1 = (-b - sqrtDiscriminant) / 2.0f;
	double t2 = (-b + sqrtDiscriminant) / 2.0f;

	if (t1 > 0) {
		glm::vec3 intersectionPoint = r.origin + static_cast<float>(t1) * r.direction;
		glm::vec3 normal = glm::normalize(intersectionPoint - this->center);
		intersectionData = { intersectionPoint, normal, glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), r.direction *= -1.0f}; //TODO Fix this ray direction stuff.

		return true;
	}
	//IF INSIDE OBJECT
	if (t2 > 0) {
		glm::vec3 intersectionPoint = r.origin + static_cast<float>(t1) * r.direction;
		glm::vec3 normal = glm::normalize(intersectionPoint - this->center);
		//TODO intersectionData = 
		intersectionData = { intersectionPoint, normal , glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), r.direction *= -1.0f }; //TODO Fix this ray direction stuff

		return true;
	}
	return false;
}

void Sphere::Transform(glm::mat4 transformMatrix) {
	//std::cout << "TRNSFORMING" << glm::to_string(transformMatrix) << std::endl;
	//std::cout << "before " << glm::to_string(this->center) << std::endl;
	this->center = transformMatrix * glm::vec4(center, 1.0);
	return;
	//std::cout << "after " << glm::to_string(this->center) << std::endl;
}

//std::tuple<glm::vec3, glm::vec3> Sphere::CalculateColor(IntersectionData& intersectionData, const Light* light)
//{
//	return this->material.CalculateRadiance(intersectionData.point, intersectionData.normal, intersectionData.incoming, intersectionData.reflection, intersectionData.viewDir, light);
//}