#ifndef COREFALL_OCTAHEDRON_H
#define COREFALL_OCTAHEDRON_H
#include "Mesh.h"
#include "glad/glad.h"

static const GLfloat g_vertex_buffer_data_octahedron[] = {
  0.0f,  1.0f,  0.0f,
  0.0f,  0.0f,  1.0f,
  1.0f,  0.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  0.0f, -1.0f,
 -1.0f,  0.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
 -1.0f,  0.0f,  0.0f,
  0.0f,  0.0f,  1.0f,
  0.0f, -1.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  0.0f,  0.0f,  1.0f,
  0.0f, -1.0f,  0.0f,
  0.0f,  0.0f, -1.0f,
  1.0f,  0.0f,  0.0f,
  0.0f, -1.0f,  0.0f,
 -1.0f,  0.0f,  0.0f,
  0.0f,  0.0f, -1.0f,
  0.0f, -1.0f,  0.0f,
  0.0f,  0.0f,  1.0f,
 -1.0f,  0.0f,  0.0f
};


static const GLfloat g_color_buffer_data_octahedron[] = {
   0.0f,  1.0f,  0.0f,
   0.0f,  0.0f,  1.0f,
   1.0f,  0.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   1.0f,  0.0f,  0.0f,
   0.0f,  0.0f, -1.0f,
   0.0f,  1.0f,  0.0f,
   0.0f,  0.0f, -1.0f,
  -1.0f,  0.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
   0.0f,  0.0f,  1.0f,
   0.0f, -1.0f,  0.0f,
   1.0f,  0.0f,  0.0f,
   0.0f,  0.0f,  1.0f,
   0.0f, -1.0f,  0.0f,
   0.0f,  0.0f, -1.0f,
   1.0f,  0.0f,  0.0f,
   0.0f, -1.0f,  0.0f,
  -1.0f,  0.0f,  0.0f,
   0.0f,  0.0f, -1.0f,
   0.0f, -1.0f,  0.0f,
   0.0f,  0.0f,  1.0f,
  -1.0f,  0.0f,  0.0f
};

class Octahedron: public Mesh {
public:
    Octahedron(GLuint shaderProgram);
};

#endif //COREFALL_OCTAHEDRON_H
