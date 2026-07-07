#include "Camera.h"

Camera::Camera(glm::vec3 startPosition)
    : position(startPosition),
      lastTime(glfwGetTime()),
      isMouseLocked(true),
      firstMouse(true){
}

void Camera::computeMatricesFromInputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        isMouseLocked = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!isMouseLocked) {
            isMouseLocked = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse = true;
        }
    }

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;
    if (!isMouseLocked) {
        return;
    }

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    if (width == 0 || height == 0) return;

    if (firstMouse) {
        glfwSetCursorPos(window, width / 2.0, height / 2.0);
        firstMouse = false;
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, width / 2.0, height / 2.0);

    horizontalAngle += mouseSpeed * float((width / 2.0) - xpos);
    verticalAngle   += mouseSpeed * float((height / 2.0) - ypos);

    if (verticalAngle > 1.57f) verticalAngle = 1.57f;
    if (verticalAngle < -1.57f) verticalAngle = -1.57f;

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0.0f,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }
    
    ProjectionMatrix = glm::perspective(glm::radians(initialFov), (float)width / (float)height, near, far);
    
    ViewMatrix = glm::lookAt(
        position, 
        position + direction, 
        up
    );
}

glm::mat4 Camera::getViewMatrix() const {
    return ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return ProjectionMatrix;
}

glm::vec3 Camera::getPosition() const {
    return position;
}