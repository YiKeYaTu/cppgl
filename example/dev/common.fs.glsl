#version 330 core

#define LIGHT_DIR vec3(1.0, 1.0, 1.0)
#define LIGHT_POS vec3(10.0, 10.0, 10.0)
#define LIGHT_INTENSITY vec3(100.0, 100.0, 100.0)

layout (location = 0) out vec4 gColor1;
layout (location = 1) out vec4 gColor2;

in vec4 vPosWorld;
in vec4 vNormalWorld;

void main() {
    vec3 N = normalize(vNormalWorld.xyz);
    vec3 L = normalize(LIGHT_DIR.xyz);

    float NdotL = dot(N, L);

    vec3 diff = max(NdotL, 0.0) * LIGHT_INTENSITY / pow(length(vPosWorld.xyz - LIGHT_POS), 2.0);
    vec3 ambi = LIGHT_INTENSITY * 0.001;

    gColor1 = vec4(diff + ambi, 1.0);
}