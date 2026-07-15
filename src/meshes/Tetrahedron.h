#ifndef COREFALL_TETRAHEDRON_H
#define COREFALL_TETRAHEDRON_H
#include "glad/glad.h"
#include "Mesh.h"

static GLfloat g_vertex_buffer_data_tetrahedron[] = {
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

static GLfloat g_normal_buffer_data_tetrahedron[] = {
    0.57735f,  0.57735f, -0.57735f,
    0.57735f,  0.57735f, -0.57735f,
    0.57735f,  0.57735f, -0.57735f,
    0.57735f, -0.57735f,  0.57735f,
    0.57735f, -0.57735f,  0.57735f,
    0.57735f, -0.57735f,  0.57735f,
    -0.57735f,  0.57735f,  0.57735f,
    -0.57735f,  0.57735f,  0.57735f,
    -0.57735f,  0.57735f,  0.57735f,
    -0.57735f, -0.57735f, -0.57735f,
    -0.57735f, -0.57735f, -0.57735f,
    -0.57735f, -0.57735f, -0.57735f
};

static GLfloat g_color_buffer_data_tetrahedron[] = {
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

static GLfloat g_uv_buffer_data_tetrahedron[] = {
    0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
    0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
    0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f,
    0.0f, 0.0f,  1.0f, 0.0f,  0.5f, 1.0f
};

class Tetrahedron: public Mesh {
public:
    Tetrahedron(std::shared_ptr<Material> mat);
};

#endif //COREFALL_TETRAHEDRON_H
