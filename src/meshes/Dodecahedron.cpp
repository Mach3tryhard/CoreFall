#include "Dodecahedron.h"
#include <vector>

Dodecahedron::Dodecahedron(std::shared_ptr<Material> mat, float radius) : Mesh(mat) {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uvs;
    std::vector<GLfloat> colors;

    float scale = 0.577350269f;
    float p = 1.6180339887f * radius * scale;
    float i = 0.6180339887f * radius * scale;
    float r = radius * scale;

    glm::vec3 v[20] = {
        {-r, -r, -r}, {-r, -r, r}, {-r, r, -r}, {-r, r, r},
        {r, -r, -r}, {r, -r, r}, {r, r, -r}, {r, r, r},
        {0, -i, -p}, {0, -i, p}, {0, i, -p}, {0, i, p},
        {-i, -p, 0}, {-i, p, 0}, {i, -p, 0}, {i, p, 0},
        {-p, 0, -i}, {-p, 0, i}, {p, 0, -i}, {p, 0, i}
    };

    int faces[12][5] = {
        {0, 16, 17, 1, 12}, {1, 17, 3, 11, 9}, {1, 9, 5, 14, 12},
        {5, 9, 11, 7, 19}, {5, 19, 18, 4, 14}, {4, 18, 6, 10, 8},
        {4, 8, 0, 12, 14}, {0, 8, 10, 2, 16}, {2, 10, 6, 15, 13},
        {2, 13, 3, 17, 16}, {3, 11, 7, 15, 13}, {6, 18, 19, 7, 15}
    };

    auto addTri = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c) {
        glm::vec3 center = (a + b + c) / 3.0f;
        glm::vec3 normal = glm::cross(b - a, c - a);
        if (glm::dot(normal, center) < 0.0f) {
            vertices.insert(vertices.end(), {a.x, a.y, a.z, c.x, c.y, c.z, b.x, b.y, b.z});
        } else {
            vertices.insert(vertices.end(), {a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z});
        }
    };

    for (int f = 0; f < 12; ++f) {
        addTri(v[faces[f][0]], v[faces[f][1]], v[faces[f][2]]);
        addTri(v[faces[f][0]], v[faces[f][2]], v[faces[f][3]]);
        addTri(v[faces[f][0]], v[faces[f][3]], v[faces[f][4]]);
    }

    vertexCount = vertices.size() / 3;

    for (size_t j = 0; j < vertexCount; ++j) {
        colors.insert(colors.end(), {1.0f, 1.0f, 1.0f});
        uvs.insert(uvs.end(), {0.5f, 0.5f});
    }

    std::vector<GLfloat> normals = generateFlatNormals(vertices.data(), vertices.size() * sizeof(GLfloat));

    LoadBuffers(vertices.data(), vertices.size() * sizeof(GLfloat),
                colors.data(), colors.size() * sizeof(GLfloat),
                uvs.data(), uvs.size() * sizeof(GLfloat),
                normals.data(), normals.size() * sizeof(GLfloat));
}