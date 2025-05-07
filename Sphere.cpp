#include <glm/glm.hpp>
#include "Sphere.h"
#include "Ray.h"
#include "Mat_Phong.h"
//#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>


Sphere::Sphere(glm::vec3 center, double radius, float reflectionK, float transmissionK, std::unique_ptr<IlluminanceModel> illuminanceModel)
{
	this->center = center;
	this->radius = radius;

	this->reflectionK = reflectionK;
	this->transmissionK = transmissionK;

	this->illuminanceModel = std::move(illuminanceModel);
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
		intersectionData.point = intersectionPoint;
		intersectionData.normal = normal;
		intersectionData.viewDir = r.direction * -1.0f;
		//intersectionData = { intersectionPoint, normal, glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), r.direction * -1.0f}; //TODO Fix this ray direction stuff.

		return true;
	}
	//IF INSIDE OBJECT
	if (t2 > 0) {
		glm::vec3 intersectionPoint = r.origin + static_cast<float>(t2) * r.direction;
		glm::vec3 normal = glm::normalize(intersectionPoint - this->center);
		intersectionData.point = intersectionPoint;
		intersectionData.normal = normal;
		intersectionData.viewDir = r.direction * -1.0f;
		//intersectionData = { intersectionPoint, normal , glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), r.direction * -1.0f}; //TODO Fix this ray direction stuff

		return true;
	}
	return false;
}

void Sphere::Transform(glm::mat4 transformMatrix) {
	this->center = transformMatrix * glm::vec4(center, 1.0);
	return;
}

glm::vec3 Sphere::CalculateColor(IntersectionData& intersectionData, World& world)
{
	return this->illuminanceModel->CalculateRadiance(intersectionData, world);
}

std::tuple<float, float> Sphere::GetUVCoordinates(IntersectionData& intersectionData)
{
	return std::tuple<float, float>(); //TODO
}

std::pair<glm::vec3, glm::vec3> Sphere::GetTangentBitangent() {
	return std::pair<glm::vec3, glm::vec3>(glm::vec3(0.0f), glm::vec3(0.0f)); //TODO;
}
