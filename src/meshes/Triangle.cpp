#include "Triangle.h"
#include "glad/glad.h"

Triangle::Triangle(std::shared_ptr<Material> mat):Mesh(mat) {
    this->programID = mat->getProgramID();
    this->vertexCount = 3;

    LoadBuffers(
        g_vertex_buffer_data_triangle, sizeof(g_vertex_buffer_data_triangle),
        g_color_buffer_data_triangle, sizeof(g_color_buffer_data_triangle),
        g_uv_buffer_data_triangle, sizeof(g_uv_buffer_data_triangle),
        g_normal_buffer_data_triangle, sizeof(g_normal_buffer_data_triangle)
    );
}
