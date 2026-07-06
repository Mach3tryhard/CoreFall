#ifndef COREFALL_MESH_H
#define COREFALL_MESH_H
#include <glad/glad.h>
#include <glm/glm.hpp>

class Mesh {
protected:
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programID;
    glm::mat4 modelMatrix;
    int vertexCount;
public:
    virtual ~Mesh() {
        if (vertexbuffer != 0) {
            glDeleteBuffers(1, &vertexbuffer);
        }
    }

    Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(GLuint shaderProgram);

    void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setModelMatrix(const glm::mat4& newModel);
};


#endif //COREFALL_MESH_H
