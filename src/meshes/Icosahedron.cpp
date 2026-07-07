#include "Icosahedron.h"
#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Icosahedron::Icosahedron(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();

    float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

    std::vector<glm::vec3> baseVertices = {
        glm::vec3(-1,  t,  0), glm::vec3( 1,  t,  0), glm::vec3(-1, -t,  0), glm::vec3( 1, -t,  0),
        glm::vec3( 0, -1,  t), glm::vec3( 0,  1,  t), glm::vec3( 0, -1, -t), glm::vec3( 0,  1, -t),
        glm::vec3( t,  0, -1), glm::vec3( t,  0,  1), glm::vec3(-t,  0, -1), glm::vec3(-t,  0,  1)
    };

    for(auto& v : baseVertices) {
        v = glm::normalize(v);
    }

    int indices[] = {
        0, 11, 5,   0, 5, 1,    0, 1, 7,    0, 7, 10,   0, 10, 11,
        1, 5, 9,    5, 11, 4,   11, 10, 2,  10, 7, 6,   7, 1, 8,
        3, 9, 4,    3, 4, 2,    3, 2, 6,    3, 6, 8,    3, 8, 9,
        4, 9, 5,    2, 4, 11,   6, 2, 10,   8, 6, 7,    9, 8, 1
    };

    std::vector<float> finalVertices;
    for(int i = 0; i < 60; ++i) {
        glm::vec3 v = baseVertices[indices[i]];
        finalVertices.push_back(v.x);
        finalVertices.push_back(v.y);
        finalVertices.push_back(v.z);
    }

    for (int i=0;i<finalVertices.size();i++) {
        g_vertex_buffer_data_icosahedron[i] = finalVertices.data()[i];
        g_color_buffer_data_icosahedron[i] = finalVertices.data()[i];
    }
    this->vertexCount = 60;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_icosahedron), g_vertex_buffer_data_icosahedron, GL_STATIC_DRAW);

    const float PI = 3.14159265359f;
    std::vector<float> finalUVs;

    for (size_t i = 0; i < finalVertices.size(); i += 3) {
        glm::vec3 n = glm::normalize(glm::vec3(finalVertices[i], finalVertices[i+1], finalVertices[i+2]));

        float u = 0.5f + std::atan2(n.z, n.x) / (2.0f * PI);
        float v = 0.5f + std::asin(n.y) / PI;

        finalUVs.push_back(u);
        finalUVs.push_back(v);
    }

    for (int i = 0; i < finalUVs.size(); i++) {
        g_uv_buffer_data_icosahedron[i] = finalUVs[i];
    }

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_icosahedron), g_uv_buffer_data_icosahedron, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_icosahedron), g_color_buffer_data_icosahedron, GL_STATIC_DRAW);
}