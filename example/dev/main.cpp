#define CPPGL_DEBUG_MODE true

#include <core/shader/ShaderProgram.hpp>
#include <core/context/WindowContext.hpp>
#include <core/render/renderUnit/TriangleRenderUnit.hpp>
#include <core/buffer/RenderBufferObject.hpp>
#include <core/texture/Texture2D.hpp>
#include <core/gl/buffer/glRenderBuffer.hpp>
#include <core/gl/configurer/glDepthTestConfigurer.hpp>
#include <math/Quaternion.hpp>
#include <util/Camera.hpp>
#include "Quad.hpp"
#include "core/render/paint/Paint.hpp"

#include "Sponza.hpp"
#include "Vertexes.hpp"

int main() {
    Quad quad;
    TriangleRenderUnit quadRenderUnit = quad.asRenderUnit();
    Camera camera = Camera(Vec3f{ 0, 1, 3 }, Vec3f{ 0, 1, 0 }, Vec3f{ 0, 1, 0 });

    unsigned int width = 2000, height = 1600;

    WindowContext windowContext = WindowContext(width, height, "TEST");
    windowContext.build();
    windowContext.use();

    Sponza sponza;
    std::shared_ptr<StructuredRenderUnit> structuredRenderUnit = sponza.load();
    structuredRenderUnit->build();

    Texture2D color1 = Texture2D(width, height, glTexture2D::TextureFormat::RGBA8, nullptr);
    Texture2D color2 = Texture2D(width, height, glTexture2D::TextureFormat::R32, nullptr);
    RenderBufferObject depthRenderBufferObject = RenderBufferObject(width, height, glRenderBuffer::RenderBufferFormat::D24S8);

    Paint& screenPaint = Paint::getScreenPaint();
    Paint paint1 = Paint({ &color1, &color2 }, { &depthRenderBufferObject });
    paint1.build();

    VertexShader commonVertexShader = VertexShader("../../example/dev/common.vs.glsl");
    FragmentShader commonFragmentShader = FragmentShader("../../dev/dev/common.fs.glsl");
    VertexShader quadVertexShader = VertexShader("../../example/dev/quad.vs.glsl");
    FragmentShader quadFragmentShader = FragmentShader("../../example/dev/quad.fs.glsl");

    ShaderProgram commonShader = ShaderProgram(&commonVertexShader, &commonFragmentShader);
    ShaderProgram quadShader = ShaderProgram(&quadVertexShader, &quadFragmentShader);

    commonShader.build();
    quadShader.build();
    quadRenderUnit.build();

    auto& initWindowState = windowContext.updateState();
    double x = initWindowState.mouseState.x, y = initWindowState.mouseState.y;

    while (!windowContext.shouldClose()) {
        const WindowState& windowState = windowContext.updateState();
        const KeyboardState& keyboardState = windowState.keyboardState;
        double xpos = windowState.mouseState.x, ypos = windowState.mouseState.y;

        if (keyboardState.isKeyPressed(Keyboard::W)) {
            camera.moveForward(0.1f);
        } else if (keyboardState.isKeyPressed(Keyboard::S)) {
            camera.moveForward(-0.1f);
        }

        if (keyboardState.isKeyPressed(Keyboard::D)) {
            camera.moveRight(0.1);
        } else if (keyboardState.isKeyPressed(Keyboard::A)) {
            camera.moveRight(-0.1);
        }

        camera.moveTargetAroundSphere((xpos - x) * 1e-3, (ypos - y) * 1e-3);

        x = xpos;
        y = ypos;

        commonShader.setUniform("model", Mat4f::Identity());
        commonShader.setUniform("view", camera.asViewMatrix());
        commonShader.setUniform("proj", Mat4f::Perspective(0.01, 2000, 45.0 / 180 * M_PI, static_cast<float>(width) / height));

        paint1.use([&structuredRenderUnit, &commonShader](RenderContext& ctx) {
            ctx.clear(Vec4f { 0.4, 0.4, 0.4, 1.0 });

            ctx.configureDepthTest(
                glDepthTestConfigurer::DepthTestStatus::ENABLE_TEST
                , glDepthTestConfigurer::DepthFunc::LESS);

            ctx.configureAlphaTest(
                glAlphaTestConfigurer::ENABLE_TEST
                , glAlphaTestConfigurer::BlendFunc::SRC_ALPHA
                , glAlphaTestConfigurer::BlendFunc::ONE_MINUS_SRC_ALPHA
            );

            structuredRenderUnit->draw([&commonShader](const std::shared_ptr<RenderUnit>& renderUnit) {
                renderUnit->draw(commonShader);
            });
        });

        quadShader.setTexture(0, "quadTexture1", paint1.getColorTexture(0));
        quadShader.setTexture(1, "quadTexture2", paint1.getColorTexture(1));

        screenPaint.use([&quadShader, &quadRenderUnit](RenderContext& ctx) {
            ctx.disableDepthTest();
            ctx.clear(Vec4f { 0.4, 0.4, 0.4, 1.0 });
            quadRenderUnit.draw(quadShader);
        });

        windowContext.swapBuffers();
        windowContext.pollEvents();
    }

    return 0;
}
