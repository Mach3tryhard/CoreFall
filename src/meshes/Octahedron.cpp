#include "Octahedron.h"
#include "glad/glad.h"

Octahedron::Octahedron(GLuint shaderProgram) {
    this->programID = shaderProgram;
    this->vertexCount = 24;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_octahedron), g_vertex_buffer_data_octahedron, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_octahedron), g_color_buffer_data_octahedron, GL_STATIC_DRAW);
}
