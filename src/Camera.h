#ifndef COREFALL_CAMERA_H
#define COREFALL_CAMERA_H
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
public:
    Camera(int windowWidth, int windowHeight);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPosition(const glm::vec3& newPosition);
    void setTarget(const glm::vec3& newTarget);
};


#endif //COREFALL_CAMERA_H