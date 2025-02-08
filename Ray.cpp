#include "Ray.h"

Ray::Ray(glm::vec3 o, glm::vec3 dir) {
	this->origin = o;
	this->direction = dir;
}
