#include <glm/glm.hpp>
#include "Ray.h"
#include "Object.h"
#include "Radiance.h"
#include <vector>

#ifndef POLYGON_H
#define POLYGON_H

class Polygon : public Object {
public:
    std::vector<glm::vec3> points;

    Polygon(std::vector<glm::vec3> points, glm::vec3 rgb);

    bool Intersect(Ray* r) override;
    void Transform(glm::mat4 transformMatrix) override;

};

#endif