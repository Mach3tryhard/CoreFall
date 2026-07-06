#include "Sphere.h"
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

Sphere::Sphere(GLuint shaderProgram, int sectors, int stacks) : Mesh(shaderProgram) {
    this->programID = shaderProgram;
    this->vertexCount = 648*100;

    std::vector<float> finalVertices;
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

            finalVertices.push_back(p1.x); finalVertices.push_back(p1.y); finalVertices.push_back(p1.z);
            finalVertices.push_back(p2.x); finalVertices.push_back(p2.y); finalVertices.push_back(p2.z);
            finalVertices.push_back(p3.x); finalVertices.push_back(p3.y); finalVertices.push_back(p3.z);

            finalVertices.push_back(p3.x); finalVertices.push_back(p3.y); finalVertices.push_back(p3.z);
            finalVertices.push_back(p2.x); finalVertices.push_back(p2.y); finalVertices.push_back(p2.z);
            finalVertices.push_back(p4.x); finalVertices.push_back(p4.y); finalVertices.push_back(p4.z);
        }
    }

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(finalVertices[0]), finalVertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(finalVertices[0]), finalVertices.data(), GL_STATIC_DRAW);
}