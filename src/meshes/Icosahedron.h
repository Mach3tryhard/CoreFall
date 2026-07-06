#ifndef COREFALL_ICOSAHEDRON_H
#define COREFALL_ICOSAHEDRON_H
#include <glad/glad.h>
#include "Mesh.h"

static GLfloat g_vertex_buffer_data_icosahedron[180];

static GLfloat g_color_buffer_data_icosahedron[180];

class Icosahedron: public Mesh{
public:
    Icosahedron(GLuint shaderProgram);
};

#endif //COREFALL_ICOSAHEDRON_H
