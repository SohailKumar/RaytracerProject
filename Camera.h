#include "World.h"
#include "Radiance.h"
#include <vector>

class Camera {
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 look_at, double focalLength, double filmPlaneWidth, double filmPlaneHeight);

    std::vector<glm::vec3> RenderWorld(World* world, int windowWidth, int windowHeight);
    glm::mat4 GetViewMatrix();

    glm::vec3 position;
    glm::vec3 look_at;
    glm::vec3 up;
    double focalLength;
    double filmPlaneWidth;
    double filmPlaneHeight;
};