#include "Camera.h"

Camera::Camera(int windowWidth, int windowHeight) {
    // Initial camera coordinates from the tutorial
    position = glm::vec3(4.0f, 3.0f, 3.0f);
    target   = glm::vec3(0.0f, 0.0f, 0.0f);
    up       = glm::vec3(0.0f, 1.0f, 0.0f);

    // Perspective settings
    fov         = 45.0f;
    aspectRatio = (float)windowWidth / (float)windowHeight;
    nearPlane   = 0.1f;
    farPlane    = 100.0f;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

void Camera::setTarget(const glm::vec3& newTarget) {
    target = newTarget;
}