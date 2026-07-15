#ifndef COREFALL_OBJECT_H
#define COREFALL_OBJECT_H
#include <memory>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "../Material.h"
#include "../meshes/Mesh.h"

class Object {
private:
    Object *Parent=nullptr;
    std::vector<Object> Children;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    std::shared_ptr<Mesh> mesh=nullptr;
    std::shared_ptr<Material> material=nullptr;

public:
    Object(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale) {
        this->position=position;
        this->rotation=rotation;
        this->scale=scale;
    }

    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scl);

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

    glm::mat4 getModelMatrix() const;

    void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    void addMesh(std::shared_ptr<Mesh> addedMesh);
};


#endif //COREFALL_OBJECT_H
