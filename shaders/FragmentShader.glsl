#version 330 core

in vec3 fragmentColor;
in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;
uniform bool useVertexColor;

void main(){
    vec3 textureColor = texture(myTextureSampler, UV).rgb;

    if (useVertexColor) {
        color = textureColor * fragmentColor;
    } else {
        color = textureColor;
    }
}