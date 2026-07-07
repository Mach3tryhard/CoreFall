#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Camera.h"
#include "LoadShader.h"
#include "meshes/Cube.h"
#include "meshes/Triangle.h"
#include "meshes/Tetrahedron.h"
#include "meshes/Icosahedron.h"
#include "meshes/Octahedron.h"
#include "meshes/Sphere.h"

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "shaders/VertexShader.glsl", "shaders/FragmentShader.glsl" );
    auto defaultMaterial = std::make_shared<Material>(programID, "textures/uv_texture.dds");

    Triangle triangle(defaultMaterial);
    Cube cube(defaultMaterial);
    Octahedron octahedron(defaultMaterial);
    Icosahedron icosahedron(defaultMaterial);
    Tetrahedron tetrahedron(defaultMaterial);
    Sphere spehere1(defaultMaterial);
    Camera camera(glm::vec3(10.0f, 0.0f, 10.0f));

    // Main Engine Loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        float timeValue = glfwGetTime();

        camera.computeMatricesFromInputs(window);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();

        glm::mat4 newModel = glm::mat4(1.0f);
        newModel = glm::translate(newModel, glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 newModel1 = glm::mat4(1.0f);
        newModel1 = glm::translate(newModel1, glm::vec3(5.0f, 0.0f, 0.0f));

        glm::mat4 newModel2 = glm::mat4(1.0f);
        newModel2 = glm::translate(newModel2,  glm::vec3(10.0f, 0.0f, 1.0f));

        glm::mat4 newModel3 = glm::mat4(1.0f);
        newModel3 = glm::translate(newModel3,glm::vec3(15.0f,0.0f,0.0f));

        glm::mat4 newModel4 = glm::mat4(1.0f);
        newModel4 = glm::translate(newModel4,glm::vec3(20.0f,0.0f,0.0f));

        glm::mat4 newModel5 = glm::mat4(1.0f);
        newModel5 = glm::translate(newModel5,glm::vec3(25.0f,0.0f,0.0f));
        //newModel3 = glm::rotate(newModel3, timeValue, glm::vec3(0.0f, 0.0f, 0.0f));

        triangle.setModelMatrix(newModel);
        triangle.Draw(view, projection);

        cube.setModelMatrix(newModel1);
        cube.Draw(view,projection);

        octahedron.setModelMatrix(newModel2);
        octahedron.Draw(view,projection);

        icosahedron.setModelMatrix(newModel3);
        icosahedron.Draw(view,projection);

        tetrahedron.setModelMatrix(newModel4);
        tetrahedron.Draw(view,projection);

        spehere1.setModelMatrix(newModel5);
        spehere1.Draw(view,projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}