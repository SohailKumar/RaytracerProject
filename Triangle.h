#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <tuple>

#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include "Vertex.h"

class Triangle : public Object {
public:
    std::vector<Vertex> points;

    Triangle(std::vector<Vertex> points, Material mat);

    bool Intersect(Ray& r, IntersectionData& intersectionData) const override;
    void Transform(glm::mat4 transformMatrix) override;
    //std::tuple<glm::vec3, glm::vec3> CalculateColor(IntersectionData& intersectionData, const Light* light) override;
    glm::vec3 CalculateColor(IntersectionData& intersectionData, World& world) override;
};
