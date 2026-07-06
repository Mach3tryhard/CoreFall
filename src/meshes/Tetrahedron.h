#ifndef COREFALL_TETRAHEDRON_H
#define COREFALL_TETRAHEDRON_H
#include "glad/glad.h"
#include "Mesh.h"

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

class Tetrahedron: public Mesh {
public:
    Tetrahedron(GLuint shaderProgram);
};

#endif //COREFALL_TETRAHEDRON_H
