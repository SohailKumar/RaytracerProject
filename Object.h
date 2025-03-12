#pragma once 

#include <glm/glm.hpp>
#include <memory>

#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "IntersectionData.h"
#include "IlluminanceModel.h"

class Object {
public:
    //Object() {};

    Material material;
    std::unique_ptr<IlluminanceModel> illuminanceModel;

    virtual bool Intersect(Ray& r, IntersectionData& intersectionData) const = 0; //checks if this object intersects with Ray

    virtual void Transform(glm::mat4 transformMatrix) = 0; //setting these to 0 means that it is purely virtual function

    //virtual std::tuple<glm::vec3, glm::vec3> CalculateColor(IntersectionData& intersectionData, const Light* light) = 0;
    virtual glm::vec3 CalculateColor(IntersectionData& intersectionData, World& world) = 0;
};
