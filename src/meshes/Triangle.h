#ifndef MYENGINE_TRIANGLE_H
#define MYENGINE_TRIANGLE_H
#include "glad/glad.h"
#include <glm/glm.hpp>

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f
};

class Triangle {
private:
    GLuint vertexbuffer;
    GLuint programID;
    glm::mat4 modelMatrix;
public:
    Triangle(GLuint shaderProgram);
    void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setModelMatrix(const glm::mat4& newModel);
};


#endif //MYENGINE_TRIANGLE_H