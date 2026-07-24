#include "Loaded.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Loaded::Loaded(std::shared_ptr<Material> mat) : Mesh(mat) {
    this->programID = mat->getProgramID();
}

bool Loaded::loadOBJ(const char *path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> pureVertices;
    std::vector<glm::vec2> pureUVs;
    std::vector<glm::vec3> pureNormals;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    std::string line;
    int lineCount = 0;
    while (std::getline(file, line)) {
        lineCount++;
        std::istringstream iss(line);
        std::string lineHeader;
        iss >> lineHeader;

        if (lineHeader == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            pureVertices.push_back(vertex);
        } else if (lineHeader == "vt") {
            glm::vec2 uv;
            iss >> uv.x >> uv.y;
            pureUVs.push_back(uv);
        } else if (lineHeader == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            pureNormals.push_back(normal);
        } else if (lineHeader == "f") {
            std::string vertexData;
            std::vector<unsigned int> faceV, faceT, faceN;

            while (iss >> vertexData) {
                unsigned int v = 0, t = 0, n = 0;

                if (sscanf(vertexData.c_str(), "%u/%u/%u", &v, &t, &n) == 3) { }
                else if (sscanf(vertexData.c_str(), "%u//%u", &v, &n) == 2) { t = 0; }
                else if (sscanf(vertexData.c_str(), "%u/%u", &v, &t) == 2) { n = 0; }
                else if (sscanf(vertexData.c_str(), "%u", &v) == 1) { t = 0; n = 0; }

                faceV.push_back(v);
                faceT.push_back(t);
                faceN.push_back(n);
            }

            if (faceV.size() >= 3) {
                for (size_t i = 1; i < faceV.size() - 1; ++i) {
                    vertexIndices.push_back(faceV[0]);
                    vertexIndices.push_back(faceV[i]);
                    vertexIndices.push_back(faceV[i + 1]);

                    uvIndices.push_back(faceT[0]);
                    uvIndices.push_back(faceT[i]);
                    uvIndices.push_back(faceT[i + 1]);

                    normalIndices.push_back(faceN[0]);
                    normalIndices.push_back(faceN[i]);
                    normalIndices.push_back(faceN[i + 1]);
                }
            }
        }
    }

    for (size_t i = 0; i < vertexIndices.size(); i++) {
        if (vertexIndices[i] > 0 && vertexIndices[i] <= pureVertices.size()) {
            vertices.push_back(pureVertices[vertexIndices[i] - 1]);
        } else {
            vertices.push_back(glm::vec3(0.0f));
        }

        if (uvIndices[i] > 0 && uvIndices[i] <= pureUVs.size()) {
            uvs.push_back(pureUVs[uvIndices[i] - 1]);
        } else {
            uvs.push_back(glm::vec2(0.0f, 0.0f));
        }

        if (normalIndices[i] > 0 && normalIndices[i] <= pureNormals.size()) {
            normals.push_back(pureNormals[normalIndices[i] - 1]);
        } else {
            normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

    this->vertexCount = vertices.size();

    std::vector<float> pureWhiteColors(vertices.size() * 3, 1.0f);

    GLfloat* normalDataPtr = (GLfloat*)normals.data();
    size_t normalSize = normals.size() * sizeof(glm::vec3);
    std::vector<GLfloat> autoNormals;

    if (pureNormals.empty()) {
        autoNormals = generateFlatNormals((GLfloat*)vertices.data(), vertices.size() * sizeof(glm::vec3));
        normalDataPtr = autoNormals.data();
        normalSize = autoNormals.size() * sizeof(GLfloat);
    }

    GLfloat* uvDataPtr = (GLfloat*)uvs.data();
    size_t uvSize = uvs.size() * sizeof(glm::vec2);
    std::vector<glm::vec2> autoUVs;

    if (pureUVs.empty()) {
        const float PI = 3.14159265359f;
        for (const auto& v : vertices) {
            glm::vec3 n = glm::normalize(v);

            float u = 0.5f + std::atan2(n.z, n.x) / (2.0f * PI);
            float v_coord = 0.5f + std::asin(n.y) / PI;

            autoUVs.push_back(glm::vec2(u, v_coord));
        }
        uvDataPtr = (GLfloat*)autoUVs.data();
        uvSize = autoUVs.size() * sizeof(glm::vec2);
    }

    LoadBuffers(
        (GLfloat*)vertices.data(), vertices.size() * sizeof(glm::vec3),
        pureWhiteColors.data(),    pureWhiteColors.size() * sizeof(float),
        uvDataPtr,                 uvSize,
        normalDataPtr,             normalSize
    );

    return true;
}