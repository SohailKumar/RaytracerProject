#include <glm/glm.hpp>
#include "Ray.h"
#include "Object.h"
#include "Radiance.h"

#ifndef SPHERE_H
#define SPHERE_H

class Sphere: public Object {
public: 
    glm::vec3 center;
    double radius;
    
    Sphere();
    Sphere(glm::vec3 center, int radius, glm::vec3 rgb);

    bool Intersect(Ray* r) override;
	void Transform(glm::mat4 transformMatrix) override;

};

#endif