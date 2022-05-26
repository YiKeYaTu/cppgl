#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 vPosWorld;
out vec4 vNormalWorld;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(aPos.xyz, 1.0);

    vPosWorld = model * vec4(aPos.xyz, 1.0);
    vNormalWorld = transpose(inverse(model)) * vec4(aNormal.xyz, 0.0);
}