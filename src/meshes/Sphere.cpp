#include "Sphere.h"
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

Sphere::Sphere(std::shared_ptr<Material> mat, int sectors, int stacks) : Mesh(mat) {
    this->programID = mat->getProgramID();

    std::vector<float> finalVertices;
    std::vector<float> finalNormals;
    float radius = 1.0f;
    const float PI = 3.14159265359f;

    for (int i = 0; i < stacks; ++i) {
        float phi1 = PI * float(i) / stacks;
        float phi2 = PI * float(i + 1) / stacks;

        for (int j = 0; j < sectors; ++j) {
            float theta1 = 2.0f * PI * float(j) / sectors;
            float theta2 = 2.0f * PI * float(j + 1) / sectors;

            glm::vec3 p1(radius * std::sin(phi1) * std::cos(theta1), radius * std::cos(phi1), radius * std::sin(phi1) * std::sin(theta1));
            glm::vec3 p2(radius * std::sin(phi2) * std::cos(theta1), radius * std::cos(phi2), radius * std::sin(phi2) * std::sin(theta1));
            glm::vec3 p3(radius * std::sin(phi1) * std::cos(theta2), radius * std::cos(phi1), radius * std::sin(phi1) * std::sin(theta2));
            glm::vec3 p4(radius * std::sin(phi2) * std::cos(theta2), radius * std::cos(phi2), radius * std::sin(phi2) * std::sin(theta2));

            glm::vec3 n1 = glm::normalize(p1);
            glm::vec3 n2 = glm::normalize(p2);
            glm::vec3 n3 = glm::normalize(p3);
            glm::vec3 n4 = glm::normalize(p4);

            finalVertices.push_back(p1.x); finalVertices.push_back(p1.y); finalVertices.push_back(p1.z);
            finalVertices.push_back(p2.x); finalVertices.push_back(p2.y); finalVertices.push_back(p2.z);
            finalVertices.push_back(p3.x); finalVertices.push_back(p3.y); finalVertices.push_back(p3.z);

            finalVertices.push_back(p3.x); finalVertices.push_back(p3.y); finalVertices.push_back(p3.z);
            finalVertices.push_back(p2.x); finalVertices.push_back(p2.y); finalVertices.push_back(p2.z);
            finalVertices.push_back(p4.x); finalVertices.push_back(p4.y); finalVertices.push_back(p4.z);

            finalNormals.push_back(n1.x); finalNormals.push_back(n1.y); finalNormals.push_back(n1.z);
            finalNormals.push_back(n2.x); finalNormals.push_back(n2.y); finalNormals.push_back(n2.z);
            finalNormals.push_back(n3.x); finalNormals.push_back(n3.y); finalNormals.push_back(n3.z);

            finalNormals.push_back(n3.x); finalNormals.push_back(n3.y); finalNormals.push_back(n3.z);
            finalNormals.push_back(n2.x); finalNormals.push_back(n2.y); finalNormals.push_back(n2.z);
            finalNormals.push_back(n4.x); finalNormals.push_back(n4.y); finalNormals.push_back(n4.z);
        }
    }

    this->vertexCount = finalVertices.size() / 3;

    std::vector<float> finalUVs;

    for (int i = 0; i < stacks; ++i) {
        float v1 = float(i) / stacks;
        float v2 = float(i + 1) / stacks;

        for (int j = 0; j < sectors; ++j) {
            float u1 = float(j) / sectors;
            float u2 = float(j + 1) / sectors;

            finalUVs.push_back(u1); finalUVs.push_back(v1);
            finalUVs.push_back(u1); finalUVs.push_back(v2);
            finalUVs.push_back(u2); finalUVs.push_back(v1);

            finalUVs.push_back(u2); finalUVs.push_back(v1);
            finalUVs.push_back(u1); finalUVs.push_back(v2);
            finalUVs.push_back(u2); finalUVs.push_back(v2);
        }
    }

    LoadBuffers(
        finalVertices.data(), finalVertices.size() * sizeof(float),
        finalVertices.data(), finalVertices.size() * sizeof(float),
        finalUVs.data(),      finalUVs.size()      * sizeof(float),
        finalNormals.data(),  finalNormals.size()  * sizeof(float)
    );
}