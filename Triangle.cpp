#include <glm/glm.hpp>
#include "Triangle.h"
#include "Ray.h"
#include "Mat_Phong.h"
#include "Vertex.h"

#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(std::vector<Vertex> points, float reflectionK, float transmissionK, std::unique_ptr<IlluminanceModel> illuminanceModel) {
	this->points = points;

	this->reflectionK = reflectionK;
	this->transmissionK = transmissionK;

	this->illuminanceModel = std::move(illuminanceModel);
	//this->illuminanceModel = std::make_unique<Mat_Phong>(mat.diffuseColor, mat.specularColor, mat.ambient_k, mat.diffuse_k, mat.specular_k, mat.shiny_exp);
}	

std::tuple<float, float, float> calculateBarycentricCoordinates(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 intersectionPoint) {
	//define edge vectors
	glm::vec3 v0 = p2 - p1;
	glm::vec3 v1 = p3 - p1;
	glm::vec3 v2 = intersectionPoint - p1;

	//compute dot products for edge vectors
	float d00 = glm::dot(v0, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;

	float lambda2 = (d11 * d20 - d01 * d21) / denom;
	float lambda3 = (d00 * d21 - d01 * d20) / denom;
	float lambda1 = 1.0f - lambda2 - lambda3;

	return { lambda1, lambda2, lambda3 };
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

	auto [lambda1, lambda2, lambda3] = calculateBarycentricCoordinates(p1, p2, p3, intersectionPoint);

	if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0) {
		intersectionData = { intersectionPoint, normal * -1.0f , glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3(0.0f, 0.0f, 0.0f), r.direction };

		return true;
	}
	return false;
}

void Triangle::Transform(glm::mat4 transformMatrix) { 
	for (Vertex& point : this->points) { //you need the & to get the reference to the actual point.
		point.position = transformMatrix * glm::vec4(point.position, 1.0);
	}
}

glm::vec3 Triangle::CalculateColor(IntersectionData& intersectionData, World& world)
{
	return this->illuminanceModel->CalculateRadiance(intersectionData, world);
}

std::tuple<float, float> Triangle::GetUVCoordinates(IntersectionData& intersectionData) {
	glm::vec3 p0 = this->points[0].position;
	glm::vec3 p1 = this->points[1].position;
	glm::vec3 p2 = this->points[2].position;
	auto [alpha, beta, gamma] = calculateBarycentricCoordinates(p0, p1, p2, intersectionData.point);

	float u = alpha * this->points[0].u + beta * this->points[1].u + gamma * this->points[2].u;
	float v = alpha * this->points[0].v + beta * this->points[1].v + gamma * this->points[2].v;

	return { u, v };
}