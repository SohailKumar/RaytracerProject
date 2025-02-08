#include <glm/glm.hpp>
#include "Object.h"
#include "Ray.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    Camera();
    Camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up);

    void RenderWorld(Object* obj);

    glm::vec3 position;
    glm::vec3 look_at;
    glm::vec3 up;


};

#endif