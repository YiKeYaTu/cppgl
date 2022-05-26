#define CPPGL_DEBUG_MODE true

#include <core/shader/ShaderProgram.hpp>
#include <core/layout/Layout.hpp>
#include <core/context/WindowContext.hpp>
#include "core/render/renderUnit/TriangleRenderUnit.hpp"
#include <core/buffer/VertexBufferObject.hpp>
#include <core/buffer/RenderBufferObject.hpp>
#include <core/render/ScreenPaint.hpp>
#include <core/render/FramePaint.hpp>
#include <core/texture/Texture2D.hpp>
#include <core/gl/buffer/glRenderBuffer.hpp>
#include <core/gl/configurer/glDepthTestConfigurer.hpp>
#include <math/Quaternion.hpp>

#include "Sponza.hpp"
#include "MyTriangle.hpp"
#include "Vertexes.hpp"

auto layout = createTriangleLayout();

int main() {
    Sponza sponza;
    sponza.load();
    return 0;

    float theta1 = -360.0 / 180 * M_PI;
    float theta2 = 20.0 / 180 * M_PI;
    float theta3 = -30.0 / 180 * M_PI;
    Vec3f n1 { 0, 0, 1 };
    Vec3f n2 { 0, 1, 0 };
    Vec3f n3 { 1, 0, 0 };

    int idx = 0;
    std::vector<Quaternion> quaternions {
        Quaternion(0, n1),
        Quaternion(theta1, n1),
        Quaternion(theta2, n2),
        Quaternion(theta3, n3),
    };

    unsigned int width = 1000, height = 800;

    TriangleRenderUnit myCube = TriangleRenderUnit(&layout, &vertices1);

    WindowContext windowContext = WindowContext(width, height, "TEST");
    windowContext.build();
    windowContext.use();

    Texture2D color1 = Texture2D(width, height, glTexture2D::TextureFormat::RGBA8);
    Texture2D color2 = Texture2D(width, height, glTexture2D::TextureFormat::RGBA8);
    RenderBufferObject depthRenderBufferObject = RenderBufferObject(width, height, glRenderBuffer::RenderBufferFormat::D24S8);

    ScreenPaint& screenPaint = ScreenPaint::getScreenPaint();
    FramePaint paint1 = FramePaint({ &color1, &color2 }, { &depthRenderBufferObject });
    paint1.build();

    VertexShader vertexShader = VertexShader("../../example/dev/common.vs.glsl");
    FragmentShader commonFragmentShader = FragmentShader("../../example/dev/common.fs.glsl");
    FragmentShader quadFragmentShader = FragmentShader("../../example/dev/quad.fs.glsl");

    ShaderProgram commonShader = ShaderProgram(&vertexShader, &commonFragmentShader);
    ShaderProgram quadShader = ShaderProgram(&vertexShader, &quadFragmentShader);

    commonShader.build();
    quadShader.build();

    float elapsed = 0.0;

    while (!windowContext.shouldClose()) {
        auto [ curWidth, curHeight ] = windowContext.getViewportSize();

        if (curWidth != width || curHeight != height) {
            width = curWidth;
            height = curHeight;
            paint1.getColorTexture(0).resize(width, height);
            paint1.getColorTexture(1).resize(width, height);
        }

        screenPaint.use();
        screenPaint.clear(Vec4f { 0.4, 0.4, 0.4, 1.0 });
        glDepthTestConfigurer::configure(
            glDepthTestConfigurer::DepthTestStatus::DEPTH_TEST | glDepthTestConfigurer::DepthTestStatus::DEPTH_MASK,
            glDepthTestConfigurer::DepthFunc::LEQUAL
        );

        if (elapsed <= 1.0f && idx + 1 < quaternions.size()) {
//            commonShader.setUniform("model", quaternions[idx].slerpFaster(quaternions[idx + 1], elapsed).asRotationMatrix());
            commonShader.setUniform("model", quaternions[idx].slerp(quaternions[idx + 1], elapsed).asRotationMatrix());
            elapsed += 0.005;
        } else {
            idx ++;
            elapsed = 0.0f;
        }

        commonShader.setUniform("view", Mat4f::LookAt( Vec3f{ 0, 5, -10 }, Vec3f{ 0, 0, 0 }, Vec3f{ 0, 1, 0 } ));
        commonShader.setUniform("proj", Mat4f::Perspective(0.01, 200, 45.0 / 180 * M_PI, static_cast<float>(width) / height));

        screenPaint.draw(myCube, commonShader);

        windowContext.swapBuffers();
        windowContext.pollEvents();
    }

    return 0;
}
