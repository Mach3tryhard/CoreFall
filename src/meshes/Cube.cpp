#include "Cube.h"
#include "glad/glad.h"

Cube::Cube(GLuint shaderProgram) : Mesh(shaderProgram) {
    this->programID = shaderProgram;
    this->vertexCount = 36;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_cube), g_vertex_buffer_data_cube, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_cube), g_color_buffer_data_cube, GL_STATIC_DRAW);
}
