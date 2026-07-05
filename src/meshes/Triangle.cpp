#include "Triangle.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtc/type_ptr.hpp"

Triangle::Triangle(GLuint shaderProgram) {
    programID = shaderProgram;
    modelMatrix = glm::mat4(1.0f);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Triangle::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), // Stride
        (void*)0           // Offset
    );

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float),             // Stride
        (void*)(3 * sizeof(float))     // Offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Triangle::setModelMatrix(const glm::mat4& newModel) {
    modelMatrix = newModel;
}