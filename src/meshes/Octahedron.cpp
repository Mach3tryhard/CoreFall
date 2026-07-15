#include "Octahedron.h"
#include "glad/glad.h"

Octahedron::Octahedron(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();
    this->vertexCount = 24;

    LoadBuffers(
        (GLfloat*)g_vertex_buffer_data_octahedron, sizeof(g_vertex_buffer_data_octahedron),
        (GLfloat*)g_color_buffer_data_octahedron,  sizeof(g_color_buffer_data_octahedron),
        (GLfloat*)g_uv_buffer_data_octahedron,     sizeof(g_uv_buffer_data_octahedron),
        (GLfloat*)g_normal_buffer_data_octahedron, sizeof(g_normal_buffer_data_octahedron)
    );
}
