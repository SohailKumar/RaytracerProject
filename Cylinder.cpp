#include "Cylinder.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Cylinder::Cylinder(glm::vec3 a, glm::vec3 b, float radius, float reflectionK, float transmissionK, std::unique_ptr<IlluminanceModel> illuminanceModel)
{
	this->a = a;
	this->b = b;
	this->radius = radius;
	this->reflectionK = reflectionK;
	this->transmissionK = transmissionK;
	this->illuminanceModel = std::move(illuminanceModel);
}

bool Cylinder::Intersect(Ray& r, IntersectionData& intersectionData) const
{
    glm::vec3 ba = b - a;
	glm::vec3 oc = r.origin - a;
	float baba = glm::dot(ba, ba);
    float bard = glm::dot(ba, r.direction);
	float baoc = glm::dot(ba, oc);
    float k2 = baba - bard * bard;
	float k1 = baba * glm::dot(oc, r.direction) - baoc * bard;
	float k0 = baba * glm::dot(oc, oc) - baoc * baoc - this->radius * this->radius * baba;
	float h = k1 * k1 - k2 * k0;

	if (h < 0.0) return false;//no intersection
	h = sqrt(h);
	float t = (-k1 - h) / k2;
    // body
    float y = baoc + t * bard;
	if (y > 0.0 && y < baba) {
		glm::vec3 intersectionPoint = r.origin + t * r.direction;
		float divRad = 1 / this->radius;
		glm::vec3 normal = (oc + t * r.direction - ba * y / baba) * divRad;
		glm::vec3 pa = intersectionPoint - this->a;
		glm::vec3 ba = this->b - this->a;
		float baba = dot(ba, ba);
		float h = dot(pa, ba) / baba;
		//float divRad = 1 / this->radius;
		//if (normal != normalCheck) {
		//	std::cout << "Normal: " << glm::to_string(normal) << ", NormalCheck: " << glm::to_string(normalCheck) << std::endl;
		//}
		normal = glm::normalize(normal);

		intersectionData.point = intersectionPoint;
		intersectionData.normal = normal;
		intersectionData.viewDir = r.direction * -1.0f;

		return true;
	}

	// caps
	t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
	if (abs(k1 + k2 * t) < h) {
		glm::vec3 intersectionPoint = r.origin + t * r.direction;
		float divRad = 1 / this->radius;
		glm::vec3 normal = ba * ((y < 0.0)? -1.0f : 1.0f) / sqrt(baba);

		intersectionData.point = intersectionPoint;
		intersectionData.normal = normal;
		intersectionData.viewDir = r.direction * -1.0f;

		return true;
	}

    //float y = baoc + t * bard;
    //if (y > 0.0 && y < baba) return vec4(t, (oc + t * rd - ba * y / baba) / ra);
    //// caps
    //t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
    //if (abs(k1 + k2 * t) < h)
    //{
    //    return vec4(t, ba * sign(y) / sqrt(baba));
    //}
    //return vec4(-1.0);//no intersection
	return false;
}

void Cylinder::Transform(glm::mat4 transformMatrix)
{
	this->a = transformMatrix * glm::vec4(a, 1.0);
	this->b = transformMatrix * glm::vec4(b, 1.0);
	return;
}

glm::vec3 Cylinder::CalculateColor(IntersectionData& intersectionData, World& world)
{
	return this->illuminanceModel->CalculateRadiance(intersectionData, world);
}

std::tuple<float, float> Cylinder::GetUVCoordinates(IntersectionData& intersectionData)
{
	return std::tuple<float, float>(); //TODO
}

