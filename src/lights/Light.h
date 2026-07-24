#ifndef COREFALL_LIGHT_H
#define COREFALL_LIGHT_H

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

enum class LightType {
    AMBIENT = 0,
    POINT = 1,
    DIRECTIONAL = 2,
    SPOT = 3
};

class Light {
private:
    LightType type;
    glm::vec3 color;
    float power;
    float maxDistance;
    float cutOff;

    mutable int cachedIndex = -1;
    mutable GLuint cachedProgramID = 0;
    mutable GLuint locType;
    mutable GLuint locPos;
    mutable GLuint locDir;
    mutable GLuint locCol;
    mutable GLuint locPow;
    mutable GLuint locDist;
    mutable GLuint locCutOff;

public:
    Light(LightType lightType = LightType::POINT, glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f), float pow = 60.0f, float maxDist = 100.0f, float cutOffAngle = 12.5f);

    void setType(LightType lightType);
    void setColor(const glm::vec3& col);
    void setPower(float pow);
    void setMaxDistance(float maxDist);
    void setCutOff(float cutOffAngle);

    [[nodiscard]] LightType getType() const;
    [[nodiscard]] glm::vec3 getColor() const;
    [[nodiscard]] float getPower() const;
    [[nodiscard]] float getMaxDistance() const;
    [[nodiscard]] float getCutOff() const;

    void RenderLight(int& currentLightIndex, glm::vec3 rotation, glm::vec3 position, GLuint programID);

    void sendToShader(GLuint programID, const glm::vec3& worldPosition, const glm::vec3& worldDirection, int index) const;
};

#endif