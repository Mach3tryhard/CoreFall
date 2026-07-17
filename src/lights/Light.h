#ifndef COREFALL_LIGHT_H
#define COREFALL_LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Light {
private:
    glm::vec3 color;
    float power;

public:
    Light(glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f), float pow = 60.0f);

    void setColor(const glm::vec3& col);
    void setPower(float pow);

    [[nodiscard]] glm::vec3 getColor() const;
    [[nodiscard]] float getPower() const;

    void sendToShader(GLuint programID, const glm::vec3& worldPosition) const;
};

#endif //COREFALL_LIGHT_H