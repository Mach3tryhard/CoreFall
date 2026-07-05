#include "Tetrahedron.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Tetrahedron::Tetrahedron(GLuint shaderProgram) {
    programID = shaderProgram;
    modelMatrix = glm::mat4(1.0f);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_tetrahedron), g_vertex_buffer_data_tetrahedron, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data_tetrahedron), g_color_buffer_data_tetrahedron, GL_STATIC_DRAW);
}

void Tetrahedron::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0
    );

    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,0 , (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, 12);

    glDisableVertexAttribArray(0);
}

void Tetrahedron::setModelMatrix(const glm::mat4& newModel) {
    modelMatrix = newModel;
}
