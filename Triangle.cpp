#include <glm/glm.hpp>
#include "Triangle.h"
#include "Ray.h"
#include "Mat_Phong.h"
#include "Vertex.h"

#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(std::vector<Vertex> points, Material mat) {
	this->points = points;
	this->material = mat;
	this->illuminanceModel = std::make_unique<Mat_Phong>(mat.diffuseColor, mat.specularColor, mat.ambient_k, mat.diffuse_k, mat.specular_k, mat.shiny_exp);
}	

bool Triangle::Intersect(Ray& r, IntersectionData& intersectionData) const {
	//for each triangle
	//std::cout << "i: " << i << std::endl;
	//check plane intersection
		
	glm::vec3 p1 = this->points[0].position;
	glm::vec3 p2 = this->points[1].position;
	glm::vec3 p3 = this->points[2].position;

	glm::vec3 normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
	float denominator = glm::dot(normal, r.direction);
		
	if (denominator <= 0.0001) {
		return false;
	}

	double intersection = glm::dot(normal, p1 - r.origin) / denominator;
	if (intersection < 0) {
		return false;
	}

	//check if point is inside triangle
	glm::vec3 intersectionPoint = r.origin + static_cast<float>(intersection) * r.direction;

	glm::vec3 v0 = p2 - p1;
	glm::vec3 v1 = p3 - p1;
	glm::vec3 v2 = intersectionPoint - p1;

	float d00 = glm::dot(v0, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float vw = 1.0f - v - w;

	if (vw >= 0 && v >= 0 && w >= 0) {
		//TODO intersectionData = 
		//glm::vec3 flipNorm = glm::normalize(normal *= -1);
		//std::cout << "normal: " << flipNorm[0] << "," << flipNorm[1] << "," << flipNorm[2] << std::endl;
		intersectionData = { intersectionPoint, normal , glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), r.direction };

		return true;
	}
	return false;
}

void Triangle::Transform(glm::mat4 transformMatrix) { 
	for (Vertex& point : this->points) { //you need the & to get the reference to the actual point.
		point.position = transformMatrix * glm::vec4(point.position, 1.0);
	}
}

//glm::vec3 Triangle::CalculateColor(IntersectionData& intersectionData, World& world)
//{
//	return glm::vec3();
//}
glm::vec3 Triangle::CalculateColor(IntersectionData& intersectionData, World& world)
{
	return this->illuminanceModel->CalculateRadiance(intersectionData, world);
	//return this->material.CalculateRadiance(intersectionData.point, intersectionData.normal, intersectionData.incoming, intersectionData.reflection, intersectionData.viewDir, light);
}

//std::tuple<glm::vec3, glm::vec3> Triangle::CalculateColor(IntersectionData& intersectionData, const Light* light)
//{
//	return this->material.CalculateRadiance(intersectionData.point, intersectionData.normal, intersectionData.incoming, intersectionData.reflection, intersectionData.viewDir, light);
//}