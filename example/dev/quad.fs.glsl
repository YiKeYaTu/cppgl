#version 330 core

in vec2 vTexcoord;
out vec4 FragColor;

uniform sampler2D quadTexture1;
uniform sampler2D quadTexture2;

void main() {
    vec4 sceneColor = vec4(texture(quadTexture1, vTexcoord.xy).xyz, 1.0);
    float sceneDepth = pow(texture(quadTexture2, vTexcoord.xy).x, 100.0);

//    FragColor = vec4(sceneColor.a);
//    FragColor = (1.0 - sceneColor) * sceneDepth + sceneColor;
    FragColor = sceneColor;
}