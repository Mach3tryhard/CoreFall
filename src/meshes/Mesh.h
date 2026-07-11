#ifndef COREFALL_MESH_H
#define COREFALL_MESH_H
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../Material.h"

class Mesh {
protected:
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint colorbuffer;
    GLuint programID;
    std::shared_ptr<Material> material;
    glm::mat4 modelMatrix;
    int vertexCount;
public:
    virtual ~Mesh() {
        if (vertexbuffer != 0) glDeleteBuffers(1, &vertexbuffer);
        if (colorbuffer != 0) glDeleteBuffers(1, &colorbuffer);
        if (uvbuffer != 0) glDeleteBuffers(1, &uvbuffer);
    }

    Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(std::shared_ptr<Material> material);

    void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setModelMatrix(const glm::mat4& newModel);
};


#endif //COREFALL_MESH_H
