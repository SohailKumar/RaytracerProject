#include <glm/glm.hpp>
#include <memory>

#include "Ray.h"
#include "Material.h"
#include "Light.h"

#ifndef OBJECT_H
#define OBJECT_H

typedef struct {
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 incoming; //incoming light
    glm::vec3 reflection;
    glm::vec3 viewDir;
    std::vector<std::unique_ptr<Light>>* lights;
} IntersectionData;

class Object {
public:
    //Object() {};

    Material material;

    virtual bool Intersect(Ray& r, IntersectionData& intersectionData) const = 0; //checks if this object intersects with Ray

    virtual void Transform(glm::mat4 transformMatrix) = 0; //setting these to 0 means that it is purely virtual function

    virtual std::tuple<glm::vec3, glm::vec3> CalculateColor(IntersectionData& intersectionData, const Light* light) = 0;
};

#endif