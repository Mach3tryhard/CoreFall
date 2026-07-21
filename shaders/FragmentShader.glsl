#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;

out vec3 color;

uniform sampler2D myTextureSampler;
uniform mat4 V;

uniform int numLights;
uniform int lightTypes[16];
uniform vec3 lightColors[16];
uniform float lightPowers[16];
uniform vec3 lightPositions[16];
uniform vec3 lightDirections[16];
uniform float lightMaxDistances[16];
uniform float lightCutOffs[16];

void main(){
    vec3 MaterialDiffuseColor = texture(myTextureSampler, UV).rgb;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

    vec3 finalColor = vec3(0.0);
    vec3 n = normalize(Normal_cameraspace);
    vec3 E = normalize(EyeDirection_cameraspace);

    for(int i = 0; i < numLights; i++) {
        if (lightTypes[i] == 0) {
            finalColor += MaterialDiffuseColor * lightColors[i] * lightPowers[i];
        }
        else if (lightTypes[i] == 1) {
            float distance = length(lightPositions[i] - Position_worldspace);
            if (distance <= lightMaxDistances[i]) {
                vec3 lightPos_cameraspace = (V * vec4(lightPositions[i], 1.0)).xyz;
                vec3 vertexPos_cameraspace = (V * vec4(Position_worldspace, 1.0)).xyz;
                vec3 l = normalize(lightPos_cameraspace - vertexPos_cameraspace);

                vec3 R = reflect(-l, n);
                float cosTheta = clamp(dot(n, l), 0.0, 1.0);
                float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

                float attenuation = 1.0 - (distance / lightMaxDistances[i]);
                attenuation = clamp(attenuation, 0.0, 1.0);

                vec3 diffuse = MaterialDiffuseColor * lightColors[i] * lightPowers[i] * cosTheta / (distance * distance);
                vec3 specular = MaterialSpecularColor * lightColors[i] * lightPowers[i] * pow(cosAlpha, 5.0) / (distance * distance);

                finalColor += (diffuse + specular) * attenuation;
            }
        }
        else if (lightTypes[i] == 2) {
            vec3 lightDir_cameraspace = (V * vec4(lightDirections[i], 0.0)).xyz;
            vec3 l = normalize(-lightDir_cameraspace);

            vec3 R = reflect(-l, n);
            float cosTheta = clamp(dot(n, l), 0.0, 1.0);
            float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

            vec3 diffuse = MaterialDiffuseColor * lightColors[i] * lightPowers[i] * cosTheta;
            vec3 specular = MaterialSpecularColor * lightColors[i] * lightPowers[i] * pow(cosAlpha, 5.0);

            finalColor += diffuse + specular;
        }
        else if (lightTypes[i] == 3) {
            float distance = length(lightPositions[i] - Position_worldspace);
            if (distance <= lightMaxDistances[i]) {
                vec3 lightPos_cameraspace = (V * vec4(lightPositions[i], 1.0)).xyz;
                vec3 vertexPos_cameraspace = (V * vec4(Position_worldspace, 1.0)).xyz;
                vec3 l = normalize(lightPos_cameraspace - vertexPos_cameraspace);

                vec3 spotDir = normalize(lightDirections[i]);
                vec3 lightToVertex = normalize(Position_worldspace - lightPositions[i]);
                float theta = dot(lightToVertex, spotDir);

                if (theta > lightCutOffs[i]) {
                    vec3 R = reflect(-l, n);
                    float cosTheta = clamp(dot(n, l), 0.0, 1.0);
                    float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

                    float attenuation = 1.0 - (distance / lightMaxDistances[i]);
                    attenuation = clamp(attenuation, 0.0, 1.0);

                    vec3 diffuse = MaterialDiffuseColor * lightColors[i] * lightPowers[i] * cosTheta / (distance * distance);
                    vec3 specular = MaterialSpecularColor * lightColors[i] * lightPowers[i] * pow(cosAlpha, 5.0) / (distance * distance);

                    finalColor += (diffuse + specular) * attenuation;
                }
            }
        }
    }

    color = finalColor;
}