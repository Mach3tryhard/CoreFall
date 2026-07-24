#include "Cylinder.h"
#include <cmath>
#include <memory>
#include <vector>
#include "Mesh.h"
#include <glm/glm.hpp>

class Material;

Cylinder::Cylinder(std::shared_ptr<Material> mat, float radius, float height, int sectors) : ::Mesh(mat) {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> uvs;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> normals;

    float halfHeight = height / 2.0f;
    float sectorStep = 2.0f * 3.14159265359f / sectors;

    for (int i = 0; i < sectors; ++i) {
        float angle1 = i * sectorStep;
        float angle2 = (i + 1) * sectorStep;

        float x1 = radius * std::cos(angle1);
        float z1 = radius * std::sin(angle1);
        float x2 = radius * std::cos(angle2);
        float z2 = radius * std::sin(angle2);

        glm::vec3 n1 = glm::normalize(glm::vec3(x1, 0.0f, z1));
        glm::vec3 n2 = glm::normalize(glm::vec3(x2, 0.0f, z2));

        vertices.insert(vertices.end(), {
            x1, halfHeight, z1,
            x2, -halfHeight, z2,
            x1, -halfHeight, z1,
            x1, halfHeight, z1,
            x2, halfHeight, z2,
            x2, -halfHeight, z2
        });

        normals.insert(normals.end(), {
            n1.x, n1.y, n1.z,
            n2.x, n2.y, n2.z,
            n1.x, n1.y, n1.z,
            n1.x, n1.y, n1.z,
            n2.x, n2.y, n2.z,
            n2.x, n2.y, n2.z
        });

        vertices.insert(vertices.end(), {
            0.0f, halfHeight, 0.0f,
            x1, halfHeight, z1,
            x2, halfHeight, z2
        });

        normals.insert(normals.end(), {
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        });

        vertices.insert(vertices.end(), {
            0.0f, -halfHeight, 0.0f,
            x2, -halfHeight, z2,
            x1, -halfHeight, z1
        });

        normals.insert(normals.end(), {
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f
        });
    }

    vertexCount = vertices.size() / 3;

    for (size_t i = 0; i < vertexCount; ++i) {
        colors.insert(colors.end(), {1.0f, 1.0f, 1.0f});
        uvs.insert(uvs.end(), {0.5f, 0.5f});
    }

    LoadBuffers(vertices.data(), vertices.size() * sizeof(GLfloat),
                colors.data(), colors.size() * sizeof(GLfloat),
                uvs.data(), uvs.size() * sizeof(GLfloat),
                normals.data(), normals.size() * sizeof(GLfloat));
}