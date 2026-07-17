#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::shared_ptr<Material> mat) {
    material = mat;
    modelMatrix = glm::mat4(1.0f);
}

void Mesh::LoadBuffers(GLfloat* vertexBuffer, size_t vSize, GLfloat* colorBuffer, size_t cSize,GLfloat* uvBuffer, size_t uSize,GLfloat* normalBuffer, size_t nSize) {

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vSize, vertexBuffer, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, cSize, colorBuffer, GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uSize, uvBuffer, GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, nSize, normalBuffer, GL_STATIC_DRAW);
}

void Mesh::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    material->Bind();

    GLuint useColorID = glGetUniformLocation(material->getProgramID(), "useVertexColor");
    glUniform1i(useColorID, 0);

    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    GLuint MatrixID = glGetUniformLocation(material->getProgramID(), "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    GLuint modelMatrixID = glGetUniformLocation(material->getProgramID(), "M");
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

    GLuint viewMatrixID = glGetUniformLocation(material->getProgramID(), "V");
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

std::vector<GLfloat> Mesh::generateFlatNormals(const GLfloat* vertices, size_t numBytes) {
    std::vector<GLfloat> normals;
    size_t floatCount = numBytes / sizeof(GLfloat);

    for (size_t i = 0; i < floatCount; i += 9) {
        glm::vec3 v0(vertices[i],     vertices[i+1], vertices[i+2]);
        glm::vec3 v1(vertices[i+3],   vertices[i+4], vertices[i+5]);
        glm::vec3 v2(vertices[i+6],   vertices[i+7], vertices[i+8]);

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        for(int j = 0; j < 3; j++) {
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
        }
    }
    return normals;
}

void Mesh::setModelMatrix(const glm::mat4& newModel) {
    modelMatrix = newModel;
}
