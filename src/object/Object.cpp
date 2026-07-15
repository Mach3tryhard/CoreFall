#include "Object.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Object::setPosition(const glm::vec3& pos) { this->position = pos; }
void Object::setRotation(const glm::vec3& rot) { rotation = rot; }
void Object::setScale(const glm::vec3& scl) { scale = scl; }

glm::vec3 Object::getPosition() const { return position; }
glm::vec3 Object::getRotation() const { return rotation; }
glm::vec3 Object::getScale() const { return scale; }

glm::mat4 Object::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::scale(model, scale);

    return model;
}

void Object::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    if (mesh) {
        mesh->setModelMatrix(getModelMatrix());
        mesh->Draw(viewMatrix, projectionMatrix);
    }
}

void Object::addMesh(std::shared_ptr<Mesh> addedMesh) {
    this->mesh = addedMesh;
}