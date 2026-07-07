#ifndef COREFALL_CONTROLS_H
#define COREFALL_CONTROLS_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 position;
    float horizontalAngle=3.14f;
    float verticalAngle=0.0f;

    float initialFov=70;
    float speed=6.0f;
    float mouseSpeed=0.005f;
    float near=0.01f;
    float far=1000.0f;

    double lastTime;
    bool isMouseLocked;
    bool firstMouse;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

public:
    Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 5.0f));

    void computeMatricesFromInputs(GLFWwindow* window);

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] glm::mat4 getProjectionMatrix() const;
    [[nodiscard]] glm::vec3 getPosition() const;
};

#endif //COREFALL_CONTROLS_H
