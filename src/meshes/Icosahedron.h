#ifndef COREFALL_ICOSAHEDRON_H
#define COREFALL_ICOSAHEDRON_H
#include <glad/glad.h>
#include <glm/glm.hpp>

class Icosahedron {
private:
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programID;
    glm::mat4 modelMatrix;
    int vertexCount;

public:
    Icosahedron(GLuint shaderProgram);
    void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setModelMatrix(const glm::mat4& newModel);
};

#endif //COREFALL_ICOSAHEDRON_H
