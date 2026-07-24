#include "Light.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

Light::Light(LightType lightType, glm::vec3 col, float pow, float maxDist, float cutOffAngle)
    : type(lightType), color(col), power(pow), maxDistance(maxDist), cutOff(glm::cos(glm::radians(cutOffAngle))) {}

void Light::setType(LightType lightType) {
    type = lightType;
}

void Light::setColor(const glm::vec3& col) {
    color = col;
}

void Light::setPower(float pow) {
    power = pow;
}

void Light::setMaxDistance(float maxDist) {
    maxDistance = maxDist;
}

void Light::setCutOff(float cutOffAngle) {
    cutOff = glm::cos(glm::radians(cutOffAngle));
}

LightType Light::getType() const {
    return type;
}

glm::vec3 Light::getColor() const {
    return color;
}

float Light::getPower() const {
    return power;
}

float Light::getMaxDistance() const {
    return maxDistance;
}

float Light::getCutOff() const {
    return cutOff;
}

void Light::sendToShader(GLuint programID, const glm::vec3& worldPosition, const glm::vec3& worldDirection, int index) const {
    if (cachedIndex != index || cachedProgramID != programID) {
        cachedIndex = index;
        cachedProgramID = programID;

        std::string typeStr = "lightTypes[" + std::to_string(index) + "]";
        std::string posStr = "lightPositions[" + std::to_string(index) + "]";
        std::string dirStr = "lightDirections[" + std::to_string(index) + "]";
        std::string colStr = "lightColors[" + std::to_string(index) + "]";
        std::string powStr = "lightPowers[" + std::to_string(index) + "]";
        std::string distStr = "lightMaxDistances[" + std::to_string(index) + "]";
        std::string cutOffStr = "lightCutOffs[" + std::to_string(index) + "]";

        locType = glGetUniformLocation(programID, typeStr.c_str());
        locPos = glGetUniformLocation(programID, posStr.c_str());
        locDir = glGetUniformLocation(programID, dirStr.c_str());
        locCol = glGetUniformLocation(programID, colStr.c_str());
        locPow = glGetUniformLocation(programID, powStr.c_str());
        locDist = glGetUniformLocation(programID, distStr.c_str());
        locCutOff = glGetUniformLocation(programID, cutOffStr.c_str());
    }

    glUniform1i(locType, static_cast<int>(type));
    glUniform3fv(locPos, 1, glm::value_ptr(worldPosition));
    glUniform3fv(locDir, 1, glm::value_ptr(worldDirection));
    glUniform3fv(locCol, 1, glm::value_ptr(color));
    glUniform1f(locPow, power);
    glUniform1f(locDist, maxDistance);
    glUniform1f(locCutOff, cutOff);
}

void Light::RenderLight(int& currentLightIndex, glm::vec3 rotation, glm::vec3 position, GLuint programID) {
    glm::mat4 rotMatrix = glm::mat4(1.0f);
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 calculatedDirection = glm::normalize(glm::vec3(rotMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));

    sendToShader(programID, position, calculatedDirection, currentLightIndex);
    currentLightIndex++;
}