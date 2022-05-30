#define CPPGL_DEBUG_MODE true

#include <core/shader/ShaderProgram.hpp>
#include <core/context/WindowContext.hpp>
#include <core/render/renderUnit/TriangleRenderUnit.hpp>
#include <core/buffer/RenderBufferObject.hpp>
#include <core/render/ScreenPaint.hpp>
#include <core/render/FramePaint.hpp>
#include <core/texture/Texture2D.hpp>
#include <core/gl/buffer/glRenderBuffer.hpp>
#include <core/gl/configurer/glDepthTestConfigurer.hpp>
#include <math/Quaternion.hpp>
#include <util/Camera.hpp>

#include "Sponza.hpp"
#include "Vertexes.hpp"

int main() {
    Camera camera = Camera(Vec3f{ 0, 1, 3 }, Vec3f{ 0, 1, 0 }, Vec3f{ 0, 1, 0 });

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

    unsigned int width = 2000, height = 1600;

//    TriangleRenderUnit myCube = TriangleRenderUnit(&layout, &vertices1);

    WindowContext windowContext = WindowContext(width, height, "TEST");
    windowContext.build();
    windowContext.use();

    Sponza sponza;
    std::shared_ptr<StructuredRenderUnit> structuredRenderUnit = sponza.load();
    structuredRenderUnit->build();

    Texture2D color1 = Texture2D(width, height, glTexture2D::TextureFormat::RGBA8, nullptr);
    Texture2D color2 = Texture2D(width, height, glTexture2D::TextureFormat::RGBA8, nullptr);
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
    auto [ x, y ] = windowContext.getMousePos();

    while (!windowContext.shouldClose()) {
        auto [ curWidth, curHeight ] = windowContext.getViewportSize();
        auto [ xpos, ypos ] = windowContext.getMousePos();

        if (windowContext.getPressedKey() == GLFW_KEY_W) {
            camera.moveForward(0.1f);
        } else if (windowContext.getPressedKey() == GLFW_KEY_S) {
            camera.moveForward(-0.1f);
        }

        if (windowContext.getPressedKey() == GLFW_KEY_D) {
            camera.moveRight(0.1);
        } else if (windowContext.getPressedKey() == GLFW_KEY_A) {
            camera.moveRight(-0.1);
        }

        camera.moveTargetAroundSphere((xpos - x) * 1e-3, (ypos - y) * 1e-3);

        x = xpos;
        y = ypos;

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

//        if (elapsed <= 1.0f && idx + 1 < quaternions.size()) {
//            commonShader.setUniform("model", quaternions[idx].slerp(quaternions[idx + 1], elapsed).asRotationMatrix());
//            elapsed += 0.005;
//        } else {
//            idx ++;
//            elapsed = 0.0f;
//        }

        commonShader.setUniform("model", Mat4f::Identity());
        commonShader.setUniform("view", camera.asViewMatrix());
        commonShader.setUniform("proj", Mat4f::Perspective(0.01, 2000, 45.0 / 180 * M_PI, static_cast<float>(width) / height));

        structuredRenderUnit->draw([&commonShader](const std::shared_ptr<RenderUnit>& renderUnit) {
            renderUnit->draw(commonShader);
        });

        windowContext.swapBuffers();
        windowContext.pollEvents();
    }

    return 0;
}
