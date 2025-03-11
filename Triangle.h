#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <tuple>

#include "Ray.h"
#include "Object.h"
#include "Material.h"

class Triangle : public Object {
public:
    std::vector<glm::vec3> points;

    Triangle(std::vector<glm::vec3> points, Material mat);

    bool Intersect(Ray& r, IntersectionData& intersectionData) const override;
    void Transform(glm::mat4 transformMatrix) override;
    //std::tuple<glm::vec3, glm::vec3> CalculateColor(IntersectionData& intersectionData, const Light* light) override;
};
