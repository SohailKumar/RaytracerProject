#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Ray.h"
#include "Object.h"
#include "Material.h"

class Triangle : public Object {
public:
    std::vector<glm::vec3> points;

    Triangle(std::vector<glm::vec3> points, glm::vec3 radianceValues);

    bool Intersect(Ray& r) override;
    void Transform(glm::mat4 transformMatrix) override;

};
