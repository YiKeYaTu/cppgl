#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vTexcoord;

void main() {
    gl_Position = vec4(aPos.xyz, 1.0);
    vTexcoord = aTex;
}