#include "Cube.h"
#include <iostream>
#include "glad/glad.h"

Cube::Cube(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();
    this->vertexCount = 36;

    LoadBuffers(
        g_vertex_buffer_data_cube, sizeof(g_vertex_buffer_data_cube),
        g_color_buffer_data_cube, sizeof(g_color_buffer_data_cube),
        g_uv_buffer_data_cube, sizeof(g_uv_buffer_data_cube),
        g_normal_buffer_data_cube, sizeof(g_normal_buffer_data_cube)
    );
}
