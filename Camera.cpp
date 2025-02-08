#include "Camera.h"

Camera::Camera() {
    this->position = glm::vec3(0.0f, 0.0f, -2.0f);
    this->look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    this->up = glm::vec3(0.0f, 0.0f, 0.0f);
}
Camera::Camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up) {
    this->position = position;
    this->look_at = look_at;
    this->up = up;
}


void Camera::RenderWorld(Object* obj) {
    

	return;
};
