#include <glm/glm.hpp>
#include "Ray.h"

#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    Object() {
        return;
    };

    bool Intersect(Ray r); //checks if this object intersects with Ray

    void Transform();
};

#endif