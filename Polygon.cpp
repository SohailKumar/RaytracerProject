#include <glm/glm.hpp>
#include "Polygon.h"
#include "Ray.h"

#include <iostream>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>

Polygon::Polygon(std::vector<glm::vec3> points, glm::vec3 rgb) {
	this->points = points;
	this->rgb = rgb;
}	

bool Polygon::Intersect(Ray* r) {
	
	//for each triangle
	for (int i = 0; i < this->points.size()-2; i++) 
	{
		//std::cout << "i: " << i << std::endl;
		//check plane intersection
		glm::vec3 p1 = this->points[i];
		glm::vec3 p2 = this->points[i + 1];
		glm::vec3 p3 = this->points[i + 2];

		glm::vec3 normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
		float denominator = glm::dot(normal, r->direction);
		
		if (denominator <= 0.0001) {
			return false;
		}

		double intersection = glm::dot(normal, p1 - r->origin) / denominator;
		if (intersection < 0) {
			return false;
		}

		//check if point is inside triangle
		glm::vec3 intersectionPoint = r->origin + static_cast<float>(intersection) * r->direction;

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
			return true;
		}
		return false;
	}

	return false;
}

void Polygon::Transform(glm::mat4 transformMatrix) {
	for (glm::vec3& point : this->points) { //you need the & to get the reference to the actual point.
		point = transformMatrix * glm::vec4(point, 1.0);
	}
}