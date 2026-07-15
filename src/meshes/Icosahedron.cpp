#include "Icosahedron.h"
#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Icosahedron::Icosahedron(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();

    std::vector<float> finalVertices;
    std::vector<float> finalNormals;

    float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

    std::vector baseVertices = {
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

    for(int i = 0; i < 60; i += 3) {
        glm::vec3 v1 = baseVertices[indices[i]];
        glm::vec3 v2 = baseVertices[indices[i+1]];
        glm::vec3 v3 = baseVertices[indices[i+2]];

        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v1;
        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        finalVertices.push_back(v1.x); finalVertices.push_back(v1.y); finalVertices.push_back(v1.z);
        finalVertices.push_back(v2.x); finalVertices.push_back(v2.y); finalVertices.push_back(v2.z);
        finalVertices.push_back(v3.x); finalVertices.push_back(v3.y); finalVertices.push_back(v3.z);

        for(int j = 0; j < 3; j++) {
            finalNormals.push_back(normal.x);
            finalNormals.push_back(normal.y);
            finalNormals.push_back(normal.z);
        }
    }

    this->vertexCount = 60;

    const float PI = 3.14159265359f;
    std::vector<float> finalUVs;

    for (size_t i = 0; i < finalVertices.size(); i += 3) {
        glm::vec3 n = glm::normalize(glm::vec3(finalVertices[i], finalVertices[i+1], finalVertices[i+2]));

        float u = 0.5f + std::atan2(n.z, n.x) / (2.0f * PI);
        float v = 0.5f + std::asin(n.y) / PI;

        finalUVs.push_back(u);
        finalUVs.push_back(v);
    }

    LoadBuffers(
        finalVertices.data(), finalVertices.size() * sizeof(float),
        finalVertices.data(), finalVertices.size() * sizeof(float),
        finalUVs.data(),      finalUVs.size()      * sizeof(float),
        finalNormals.data(),  finalNormals.size()  * sizeof(float)
    );
}