#include "Trapezohedron.h"
#include <cmath>
#include <vector>

Trapezohedron::Trapezohedron(std::shared_ptr<Material> mat, float radius, float height) : Mesh(mat) {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uvs;
    std::vector<GLfloat> colors;

    std::vector<glm::vec3> pts(12);
    pts[0] = glm::vec3(0.0f, height, 0.0f);
    pts[11] = glm::vec3(0.0f, -height, 0.0f);

    float h = height * 0.1055728f;
    float angleStep = 2.0f * 3.14159265359f / 10.0f;

    for (int i = 0; i < 10; ++i) {
        float y = (i % 2 == 0) ? h : -h;
        pts[i + 1] = glm::vec3(radius * std::cos(i * angleStep), y, radius * std::sin(i * angleStep));
    }

    auto addTri = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c) {
        glm::vec3 center = (a + b + c) / 3.0f;
        glm::vec3 normal = glm::cross(b - a, c - a);
        if (glm::dot(normal, center) < 0.0f) {
            vertices.insert(vertices.end(), {a.x, a.y, a.z, c.x, c.y, c.z, b.x, b.y, b.z});
        } else {
            vertices.insert(vertices.end(), {a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z});
        }
    };

    for (int i = 0; i < 5; ++i) {
        int e_top0 = (2 * i) + 1;
        int e_top1 = (2 * i + 1) % 10 + 1;
        int e_top2 = (2 * i + 2) % 10 + 1;

        addTri(pts[0], pts[e_top0], pts[e_top1]);
        addTri(pts[0], pts[e_top1], pts[e_top2]);

        int e_bot0 = (2 * i + 1) % 10 + 1;
        int e_bot1 = (2 * i + 2) % 10 + 1;
        int e_bot2 = (2 * i + 3) % 10 + 1;

        addTri(pts[11], pts[e_bot0], pts[e_bot1]);
        addTri(pts[11], pts[e_bot1], pts[e_bot2]);
    }

    vertexCount = vertices.size() / 3;

    for (size_t i = 0; i < vertexCount; ++i) {
        colors.insert(colors.end(), {1.0f, 1.0f, 1.0f});
        uvs.insert(uvs.end(), {0.5f, 0.5f});
    }

    std::vector<GLfloat> normals = generateFlatNormals(vertices.data(), vertices.size() * sizeof(GLfloat));

    LoadBuffers(vertices.data(), vertices.size() * sizeof(GLfloat),
                colors.data(), colors.size() * sizeof(GLfloat),
                uvs.data(), uvs.size() * sizeof(GLfloat),
                normals.data(), normals.size() * sizeof(GLfloat));
}