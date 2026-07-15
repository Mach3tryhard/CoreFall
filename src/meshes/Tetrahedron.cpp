#include "Tetrahedron.h"
#include "glad/glad.h"

Tetrahedron::Tetrahedron(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();
    this->vertexCount = 12;

    LoadBuffers(
        (GLfloat*)g_vertex_buffer_data_tetrahedron, sizeof(g_vertex_buffer_data_tetrahedron),
        (GLfloat*)g_color_buffer_data_tetrahedron,  sizeof(g_color_buffer_data_tetrahedron),
        (GLfloat*)g_uv_buffer_data_tetrahedron,     sizeof(g_uv_buffer_data_tetrahedron),
        (GLfloat*)g_normal_buffer_data_tetrahedron, sizeof(g_normal_buffer_data_tetrahedron)
    );
}
