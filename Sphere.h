#include <glm/glm.hpp>
#include "Ray.h"
#include "Object.h"

#ifndef SPHERE_H
#define SPHERE_H

class Sphere: public Object {
public: 
    glm::vec3 center;
    int radius;

    Sphere();
    Sphere(glm::vec3 center, int radius);

    bool Intersect(Ray r);
	void Transform(glm::mat3x3 transformMatrix);

};

#endif