#include "Camera.h"
#include "Ray.h"
#include "World.h"
#include "Radiance.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Camera::Camera() {
    this->position = glm::vec3(0.0f, 0.0f, -2.0f);
    this->look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->focalLength = 1.0;
    this->filmPlaneWidth = 2;
    this->filmPlaneHeight = 2;
}
Camera::Camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up, double focalLength, double filmPlaneWidth, double filmPlaneHeight) {
    this->position = position;
    this->look_at = look_at;
    this->up = up;
    this->focalLength = focalLength;
    this->filmPlaneWidth = filmPlaneWidth;
    this->filmPlaneHeight = filmPlaneHeight;
}

std::vector<Radiance*> Camera::RenderWorld(World* world, int windowWidth, int windowHeight)
{
    double pixelWidth = this->filmPlaneWidth / windowWidth;
    double pixelHeight = this->filmPlaneHeight / windowHeight;
    std::cout << "Pixel Width: " << pixelWidth << ", Height: " << pixelHeight << std::endl;

    std::vector<Radiance*> radianceArray;

    //starting at the bottom left and going to the top right.
    for (double i = -(filmPlaneWidth / 2) ; i < (filmPlaneWidth / 2); i += pixelWidth) {
        for (double j = -(filmPlaneHeight / 2); j < (filmPlaneHeight / 2); j += pixelHeight) {

            glm::vec3 pixel = glm::vec3(i + (pixelWidth/2), j + (pixelHeight/2), -this->focalLength); // create a ray towards center of pixel.
            glm::vec3 direction = glm::normalize(pixel - glm::vec3(0,0,0));

            Radiance* radianceRet = world->spawn(Ray(glm::vec3(0, 0, 0), direction));

			//std::cout << "i: " << i+ (pixelWidth / 2) << ", j: " << j+(pixelHeight / 2) << ", Ray: " << glm::to_string(Ray(glm::vec3(0, 0, 0), direction).direction) << std::endl;
            if (radianceRet != nullptr) {
                //intersection. get color
                radianceRet->radianceValues *= 255;
                radianceArray.push_back(radianceRet);

                std::cout << "Intersection at: " << std::endl;
            }
            else {
                radianceArray.push_back(new Radiance(glm::vec3(0, 0, 0)));
            }

        }
    }

    return radianceArray;
};

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->position, this->look_at, this->up);
}
