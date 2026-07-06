#include "Tetrahedron.h"
#include "glad/glad.h"

Tetrahedron::Tetrahedron(GLuint shaderProgram) {
    this->programID = shaderProgram;
    this->vertexCount = 12;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_tetrahedron), g_vertex_buffer_data_tetrahedron, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_tetrahedron), g_color_buffer_data_tetrahedron, GL_STATIC_DRAW);
}
