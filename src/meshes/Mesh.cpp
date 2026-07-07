#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::shared_ptr<Material> mat) {
    material = mat;
    modelMatrix = glm::mat4(1.0f);
}

void Mesh::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    material->Bind();

    GLuint useColorID = glGetUniformLocation(material->getProgramID(), "useVertexColor");
    glUniform1i(useColorID, 0);

    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

    GLuint MatrixID = glGetUniformLocation(material->getProgramID(), "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Mesh::setModelMatrix(const glm::mat4& newModel) {
    modelMatrix = newModel;
}
