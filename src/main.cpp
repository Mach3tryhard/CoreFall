#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "LoadShader.h"
#include "meshes/Cube.h"
#include "meshes/Triangle.h"
#include "meshes/Tetrahedron.h"
#include "meshes/Icosahedron.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Engine Runtime", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "shaders/VertexShader.glsl", "shaders/FragmentShader.glsl" );

    Triangle triangle1(programID);
    Cube cube1(programID);
    Tetrahedron d4(programID);
    Icosahedron d20(programID);
    Camera mainCamera(1920, 1080);

    // Main Engine Loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        float timeValue = glfwGetTime();

        glm::mat4 newModel = glm::mat4(1.0f);
        newModel = glm::translate(newModel, glm::vec3(-3.0f, 0.0f, 0.0f));
        newModel = glm::rotate(newModel, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 newModel1 = glm::mat4(1.0f);
        newModel1 = glm::rotate(newModel1, timeValue, glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 newModel2 = glm::mat4(1.0f);
        newModel2 = glm::rotate(newModel2, timeValue, glm::vec3(.0f, 0.0f, 1.0f));

        glm::mat4 newModel3 = glm::mat4(1.0f);
        newModel3 = glm::translate(newModel3,glm::vec3(1.5f,1.5f,1.5f));
        newModel3 = glm::rotate(newModel3, timeValue, glm::vec3(.0f, 0.0f, 1.0f));

        glm::mat4 view = mainCamera.getViewMatrix();
        glm::mat4 projection = mainCamera.getProjectionMatrix();

        d20.setModelMatrix(newModel3);
        d20.Draw(view,projection);

        /*
        d4.setModelMatrix(newModel2);
        d4.Draw(view,projection);

        triangle1.setModelMatrix(newModel1);
        triangle1.Draw(view, projection);

        cube1.setModelMatrix(newModel);
        cube1.Draw(view,projection);
        */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}