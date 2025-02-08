#include <glm/glm.hpp>
#include "Ray.h"
#include "Object.h"

#ifndef PLANE_H
#define PLANE_H

class Plane : public Object {
public:
    glm::vec4 planeEquation;
    glm::vec3 normalVector;
    glm::vec3 center;


    Plane();
    Plane(glm::vec3 normalVector, glm::vec3 center);

    bool Intersect(Ray* r) override;
    void Transform(glm::mat4 transformMatrix) override;

};

#endif