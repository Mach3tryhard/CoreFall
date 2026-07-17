#include "Light.h"
#include <glm/gtc/type_ptr.hpp>

Light::Light(glm::vec3 col, float pow) : color(col), power(pow) {}

void Light::setColor(const glm::vec3& col) {
    color = col;
}
void Light::setPower(float pow) {
    power = pow;
}

glm::vec3 Light::getColor() const {
    return color;
}
float Light::getPower() const {
    return power;
}

void Light::sendToShader(GLuint programID, const glm::vec3& worldPosition) const {
    GLuint lightPosID = glGetUniformLocation(programID, "LightPosition_worldspace");
    GLuint lightColorID = glGetUniformLocation(programID, "LightColor");
    GLuint lightPowerID = glGetUniformLocation(programID, "LightPower");

    glUniform3fv(lightPosID, 1, glm::value_ptr(worldPosition));
    glUniform3fv(lightColorID, 1, glm::value_ptr(color));
    glUniform1f(lightPowerID, power);
}