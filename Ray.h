#pragma once

#include <vector>

#include <glm/glm.hpp>

class Ray {
public:
    Ray(glm::vec3 o, glm::vec3 dir);

    glm::vec3 origin;
    glm::vec3 direction;
};