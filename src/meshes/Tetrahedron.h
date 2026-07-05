#ifndef COREFALL_TETRAHEDRON_H
#define COREFALL_TETRAHEDRON_H
#include "glad/glad.h"
#include <glm/glm.hpp>

static const GLfloat g_vertex_buffer_data_tetrahedron[] = {
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
   -1.0f,  1.0f, -1.0f,

    1.0f,  1.0f,  1.0f,
   -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,

    1.0f,  1.0f,  1.0f,
   -1.0f,  1.0f, -1.0f,
   -1.0f, -1.0f,  1.0f,

   -1.0f, -1.0f,  1.0f,
   -1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f
};


static const GLfloat g_color_buffer_data_tetrahedron[] = {
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
   -1.0f,  1.0f, -1.0f,

    1.0f,  1.0f,  1.0f,
   -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,

    1.0f,  1.0f,  1.0f,
   -1.0f,  1.0f, -1.0f,
   -1.0f, -1.0f,  1.0f,

   -1.0f, -1.0f,  1.0f,
   -1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f
};

class Tetrahedron {
private:
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programID;
    glm::mat4 modelMatrix;
public:
    Tetrahedron(GLuint shaderProgram);
    void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setModelMatrix(const glm::mat4& newModel);
};

#endif //COREFALL_TETRAHEDRON_H
