#include "Octahedron.h"
#include "glad/glad.h"

Octahedron::Octahedron(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();
    this->vertexCount = 24;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_octahedron), g_vertex_buffer_data_octahedron, GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_octahedron), g_uv_buffer_data_octahedron, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_octahedron), g_color_buffer_data_octahedron, GL_STATIC_DRAW);
}
