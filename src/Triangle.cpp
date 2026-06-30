#include "Triangle.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtc/type_ptr.hpp"

Triangle::Triangle(GLuint shaderProgram) {
    programID = shaderProgram;
    modelMatrix = glm::mat4(1.0f);

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Triangle::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    // 1. Calculate the MVP matrix: Projection * View * Model
    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    // 2. Send it to the currently bound shader
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    // 3. Draw the triangle
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
}

void Triangle::setModelMatrix(const glm::mat4& newModel) {
    modelMatrix = newModel;
}