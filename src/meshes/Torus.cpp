#include "Torus.h"
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

Torus::Torus(std::shared_ptr<Material> mat, float mainRadius, float tubeRadius, int mainSectors, int tubeSectors) : Mesh(mat) {
    this->programID = mat->getProgramID();

    std::vector<float> finalVertices;
    std::vector<float> finalNormals;
    std::vector<float> finalUVs;
    std::vector<float> finalColors;
    
    const float PI = 3.14159265359f;

    auto getPosition = [&](float theta, float phi) {
        return glm::vec3(
            (mainRadius + tubeRadius * std::cos(phi)) * std::cos(theta),
            tubeRadius * std::sin(phi),
            (mainRadius + tubeRadius * std::cos(phi)) * std::sin(theta)
        );
    };

    for (int i = 0; i < mainSectors; ++i) {
        float u1 = float(i) / mainSectors;
        float u2 = float(i + 1) / mainSectors;
        float theta1 = u1 * 2.0f * PI;
        float theta2 = u2 * 2.0f * PI;

        glm::vec3 c1(mainRadius * std::cos(theta1), 0.0f, mainRadius * std::sin(theta1));
        glm::vec3 c2(mainRadius * std::cos(theta2), 0.0f, mainRadius * std::sin(theta2));

        for (int j = 0; j < tubeSectors; ++j) {
            float v1 = float(j) / tubeSectors;
            float v2 = float(j + 1) / tubeSectors;
            float phi1 = v1 * 2.0f * PI;
            float phi2 = v2 * 2.0f * PI;

            glm::vec3 p1 = getPosition(theta1, phi1);
            glm::vec3 p2 = getPosition(theta2, phi1);
            glm::vec3 p3 = getPosition(theta1, phi2);
            glm::vec3 p4 = getPosition(theta2, phi2);

            glm::vec3 n1 = glm::normalize(p1 - c1);
            glm::vec3 n2 = glm::normalize(p2 - c1);
            glm::vec3 n3 = glm::normalize(p3 - c2);
            glm::vec3 n4 = glm::normalize(p4 - c2);

            finalVertices.insert(finalVertices.end(), {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z});
            finalUVs.insert(finalUVs.end(), {u1, v1, u2, v1, u1, v2});

            finalNormals.push_back(n1.x); finalNormals.push_back(n1.y); finalNormals.push_back(n1.z);
            finalNormals.push_back(n2.x); finalNormals.push_back(n2.y); finalNormals.push_back(n2.z);
            finalNormals.push_back(n3.x); finalNormals.push_back(n3.y); finalNormals.push_back(n3.z);

            finalNormals.push_back(n3.x); finalNormals.push_back(n3.y); finalNormals.push_back(n3.z);
            finalNormals.push_back(n2.x); finalNormals.push_back(n2.y); finalNormals.push_back(n2.z);
            finalNormals.push_back(n4.x); finalNormals.push_back(n4.y); finalNormals.push_back(n4.z);

            finalVertices.insert(finalVertices.end(), {p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p4.x, p4.y, p4.z});
            finalUVs.insert(finalUVs.end(), {u1, v2, u2, v1, u2, v2});
        }
    }

    this->vertexCount = finalVertices.size() / 3;

    for(size_t i = 0; i < finalVertices.size(); i++) {
        finalColors.push_back(1.0f);
    }

    LoadBuffers(
        finalVertices.data(), finalVertices.size() * sizeof(float),
        finalColors.data(), finalColors.size() * sizeof(float),
        finalUVs.data(),      finalUVs.size()      * sizeof(float),
        finalNormals.data(),  finalNormals.size()  * sizeof(float)
    );
}