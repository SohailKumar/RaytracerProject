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
Camera::Camera(glm::vec3 position, glm::vec3 look_at, double focalLength, double filmPlaneWidth, double filmPlaneHeight) {
    this->position = position;
    this->look_at = look_at;

    glm::vec3 forward = glm::normalize(look_at - position);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(worldUp, forward));
    glm::vec3 up = glm::normalize(glm::cross(forward, right));
    this->up = up;
	std::cout << "Up: " << glm::to_string(up) << std::endl;
    
    this->focalLength = focalLength;
    this->filmPlaneWidth = filmPlaneWidth;
    this->filmPlaneHeight = filmPlaneHeight;
}

std::vector<glm::vec3> Camera::RenderWorld(World* world, int windowWidth, int windowHeight)
{
    double pixelWidth = this->filmPlaneWidth / windowWidth;
    double pixelHeight = this->filmPlaneHeight / windowHeight;
    std::cout << "Pixel Width: " << pixelWidth << ", Height: " << pixelHeight << std::endl;

    std::vector<glm::vec3> rgbArray;

    //starting at the bottom left and going to the top right.
    for (double j = (filmPlaneHeight / 2); j > -(filmPlaneHeight / 2); j -= pixelHeight) {
        for (double i = -(filmPlaneWidth / 2); i < (filmPlaneWidth / 2); i += pixelWidth) {
            glm::vec3 pixel = glm::vec3(i + (pixelWidth / 2), j + (pixelHeight / 2), -this->focalLength); // create a ray towards center of pixel.
            glm::vec3 direction = glm::normalize(pixel - glm::vec3(0, 0, 0));

            glm::vec3 rgbRet = world->spawn(Ray(glm::vec3(0, 0, 0), direction));

            //std::cout << "i: " << i << ", j: " << j << ", Ray: " << glm::to_string(Ray(glm::vec3(0, 0, 0), direction).direction) << std::endl;

            rgbRet *= 255;
            rgbArray.push_back(rgbRet);
        }
    }
   // for (double i = -(filmPlaneWidth / 2) ; i < (filmPlaneWidth / 2); i += pixelWidth) {
   //     for (double j = (filmPlaneHeight / 2); j > -(filmPlaneHeight / 2); j -= pixelHeight) {

   //         glm::vec3 pixel = glm::vec3(i + (pixelWidth/2), j + (pixelHeight/2), -this->focalLength); // create a ray towards center of pixel.
   //         glm::vec3 direction = glm::normalize(pixel - glm::vec3(0,0,0));

   //         glm::vec3 rgbRet = world->spawn(Ray(glm::vec3(0, 0, 0), direction));

			//std::cout << "i: " << i << ", j: " << j << ", Ray: " << glm::to_string(Ray(glm::vec3(0, 0, 0), direction).direction) << std::endl;

   //         rgbRet *= 255;
   //         rgbArray.push_back(rgbRet);

   //     }
   // }

    return rgbArray;
};

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->position, this->look_at, this->up);
}
