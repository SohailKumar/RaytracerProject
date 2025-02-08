#include <glm/glm.hpp>
#include "Ray.h"
#include "Object.h"

#ifndef PLANE_H
#define PLANE_H

class Plane : public Object {
public:
    glm::vec4 planeEquation;


    Plane();
    Plane(glm::vec4 equation);
    Plane(glm::vec3 normalVector, glm::vec3 center);

    bool Intersect(Ray r);
    void Transform(glm::mat3x3 transformMatrix);

};

#endif