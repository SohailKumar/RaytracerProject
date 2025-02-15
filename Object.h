#include <glm/glm.hpp>
#include "Ray.h"
#include "Radiance.h"

#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    Radiance* radiance;
    glm::vec3 rgb;

    virtual bool Intersect(Ray* r) = 0; //checks if this object intersects with Ray

    virtual void Transform(glm::mat4 transformMatrix) = 0;
};

#endif