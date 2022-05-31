#version 330 core

layout (location = 0) out vec4 FragColor1;
layout (location = 1) out float FragColor2;

in vec4 vPosWorld;
in vec4 vPosClip;
in vec4 vNormalWorld;
in vec2 vTexcoord;

uniform sampler2D diffuseTexture0;
uniform sampler2D ambientTexture0;
uniform sampler2D heightTexture0;

uniform sampler2D previousColorTexture;
uniform sampler2D previousDepthTexture;
uniform bool enableComparison;

void main() {
    vec4 vPosNDC = (vPosClip / vPosClip.w) * 0.5 + 0.5;
    vec4 currentColor = texture(diffuseTexture0, 1.0 - vTexcoord);

    if (enableComparison) {
        if (vPosNDC.z <= texture(previousDepthTexture,vPosNDC.xy).r) {
            discard;
        }
    }

    FragColor1 = vec4(currentColor.rgb, 0.5);
    FragColor2 = vPosNDC.z;
}