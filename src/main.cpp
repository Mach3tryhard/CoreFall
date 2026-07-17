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
#include "meshes/Loaded.h"
#include "meshes/Octahedron.h"
#include "meshes/Sphere.h"
#include "meshes/Torus.h"
#include "object/Object.h"

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

    auto uvMaterial = std::make_shared<Material>(programID, "textures/uv_texture.dds");
    auto defaultMaterial = std::make_shared<Material>(programID, "textures/default.dds");

    auto trianglemesh = std::make_shared<Triangle>(defaultMaterial);

    auto sphereMesh = std::make_shared<Sphere>(defaultMaterial);
    auto torusMesh = std::make_shared<Torus>(defaultMaterial);

    auto cubeMesh = std::make_shared<Cube>(defaultMaterial);
    auto tetrahedronMesh = std::make_shared<Tetrahedron>(defaultMaterial);
    auto octahedronMesh = std::make_shared<Octahedron>(defaultMaterial);
    auto icosahedronMesh = std::make_shared<Icosahedron>(defaultMaterial);

    auto loadedMesh = std::make_shared<Loaded>(defaultMaterial);
    loadedMesh->loadOBJ("models/monkey.obj");

    auto elementLight = std::make_shared<Light>(glm::vec3(1.0f,1.0f,1.0f),80);

    Object TRIANGLE(glm::vec3(2.5f,0.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    TRIANGLE.addMesh(trianglemesh);

    Object SPHERE(glm::vec3(5.0f,0.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    SPHERE.addMesh(sphereMesh);
    Object TORUS(glm::vec3(7.5f,0.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    TORUS.addMesh(torusMesh);

    Object CUBE(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    CUBE.addMesh(cubeMesh);
    Object TETRAHEDRON(glm::vec3(10.0f,0.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    TETRAHEDRON.addMesh(tetrahedronMesh);
    Object OCTAHEDRON(glm::vec3(0.0f,5.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    OCTAHEDRON.addMesh(octahedronMesh);
    Object ICOSAHEDRON(glm::vec3(2.5f,5.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    ICOSAHEDRON.addMesh(icosahedronMesh);

    Object MONKEY(glm::vec3(5.0f,5.0f,0.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    MONKEY.addMesh(loadedMesh);

    Object LIGHT(glm::vec3(5.0f,2.5f,10.0f),glm::vec3(0.0f),glm::vec3(1.0f));
    LIGHT.addLight(elementLight);

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

    // Main Engine Loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        if (LIGHT.getLight() != nullptr) {
            LIGHT.getLight()->sendToShader(programID, LIGHT.getPosition());
        }

        camera.computeMatricesFromInputs(window);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();

        CUBE.Draw(view,projection);
        TRIANGLE.Draw(view,projection);
        SPHERE.Draw(view,projection);
        TORUS.Draw(view,projection);
        TETRAHEDRON.Draw(view,projection);
        OCTAHEDRON.Draw(view,projection);
        ICOSAHEDRON.Draw(view,projection);
        MONKEY.Draw(view,projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}