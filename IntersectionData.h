#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include "Light.h" // Forward declare if Light is complex

typedef struct {
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 incoming; //incoming light
    glm::vec3 reflection;
    glm::vec3 viewDir;
    std::vector<std::unique_ptr<Light>>* lights;
} IntersectionData;