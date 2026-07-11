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

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

    std::vector<float> pureWhiteColors;
    for(size_t i = 0; i < vertices.size() * 3; i++) {
        pureWhiteColors.push_back(1.0f);
    }

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, pureWhiteColors.size() * sizeof(float), pureWhiteColors.data(), GL_STATIC_DRAW);

    return true;
}