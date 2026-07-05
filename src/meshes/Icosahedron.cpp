#include "Icosahedron.h"
#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Icosahedron::Icosahedron(GLuint shaderProgram) {
    programID = shaderProgram;
    modelMatrix = glm::mat4(1.0f);

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
    
    vertexCount = 60;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(float), finalVertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(float), finalVertices.data(), GL_STATIC_DRAW);
}

void Icosahedron::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(0);
}

void Icosahedron::setModelMatrix(const glm::mat4& newModel) {
    modelMatrix = newModel;
}