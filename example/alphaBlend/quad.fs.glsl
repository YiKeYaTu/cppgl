#version 330 core

in vec2 vTexcoord;
out vec4 FragColor;

uniform sampler2D colorTexture0;
uniform sampler2D colorTexture1;
uniform int numPasses;

void main() {
    vec4 sceneColors[2] = vec4[2](
        texture(colorTexture0, vTexcoord.xy),
        texture(colorTexture1, vTexcoord.xy)
    );

    vec4 finalColor = vec4(0.0);

    for (int i = numPasses - 1; i > -1; i --) {
        finalColor = vec4(
            finalColor.rgb * finalColor.a + sceneColors[i].rgb * (1.0 - finalColor.a)
            , sceneColors[i].a
        );
    }

//    FragColor = vec4(vTexcoord.xy, 1.0, 1.0);
    FragColor = finalColor;

    //    FragColor = vec4(sceneColor.a);
    //    FragColor = (1.0 - sceneColor) * sceneDepth + sceneColor;
}