#include <glm/glm.hpp>

#ifndef RAY_H
#define RAY_H

class Ray {
public:
    Ray(glm::vec3 o, glm::vec3 dir);

    glm::vec3 origin;
    glm::vec3 direction;
};

#endif