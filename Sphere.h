#include <glm/glm.hpp>
#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include "Light.h"

#ifndef SPHERE_H
#define SPHERE_H

class Sphere: public Object {
public: 
    glm::vec3 center;
    double radius;
    
    Sphere(glm::vec3 center, double radius, float reflectionK, float transmissionK, std::unique_ptr<IlluminanceModel> illuminanceModel);

    bool Intersect(Ray& r, IntersectionData& intersectionData) const override;
	void Transform(glm::mat4 transformMatrix) override;
    //std::tuple<glm::vec3, glm::vec3> CalculateColor(IntersectionData& intersectionData, const Light* light) override;
    glm::vec3 CalculateColor(IntersectionData& intersectionData, World& world) override;
    std::tuple<float, float> GetUVCoordinates(IntersectionData& intersectionData) override;
    std::pair<glm::vec3, glm::vec3> GetTangentBitangent() override;
};

#endif