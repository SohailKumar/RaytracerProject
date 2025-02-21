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
    glm::vec3 incoming;
    glm::vec3 reflective;
    std::vector<std::unique_ptr<Light>>* lights;
} IntersectionData;

class Object {
public:
    //Object() {};

    Material material;
    glm::vec3 rgb;

    virtual bool Intersect(Ray& r, IntersectionData& intersectionData) const = 0; //checks if this object intersects with Ray

    virtual void Transform(glm::mat4 transformMatrix) = 0; //setting these to 0 means that it is purely virtual function

    virtual glm::vec3 CalculateColor(IntersectionData& intersectionData, std::vector<std::unique_ptr<Light>>* lights) const = 0;
};

#endif