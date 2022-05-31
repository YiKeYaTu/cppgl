#version 330 core

layout (location = 0) out vec4 FragColor1;
layout (location = 1) out float FragColor2;

in vec4 vPosWorld;
in vec4 vNormalWorld;
in vec2 vTexcoord;

uniform sampler2D diffuseTexture0;
uniform sampler2D ambientTexture0;
uniform sampler2D heightTexture0;

void main() {
    FragColor1 = vec4(texture(diffuseTexture0, 1.0 - vTexcoord).xyz, 0.5);
    FragColor2 = gl_FragCoord.z;
}