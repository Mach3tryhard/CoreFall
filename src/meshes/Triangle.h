#ifndef MYENGINE_TRIANGLE_H
#define MYENGINE_TRIANGLE_H
#include "glad/glad.h"
#include "Mesh.h"

static const GLfloat g_vertex_buffer_data_triangle[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
};

static const GLfloat g_color_buffer_data_triangle[] = {
    1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
};

class Triangle: public Mesh {
public:
    Triangle(GLuint shaderProgram);
};


#endif //MYENGINE_TRIANGLE_H