#version 330 core

in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D quadTexture1;
uniform sampler2D quadTexture2;

void main() {
    if (vTexCoord.x < 0.5) {
        FragColor = vec4(texture(quadTexture1, vTexCoord.xy).xyz, 1.0);
    } else {
        FragColor = vec4(texture(quadTexture2, vTexCoord.xy).xyz, 1.0);
    }
}