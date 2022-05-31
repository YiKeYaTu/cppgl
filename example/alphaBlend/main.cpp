//
// Created by lc on 2022/5/30.
//

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

#define NUM_PASSES 3

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

    std::vector<Texture2D> textures;
    std::vector<RenderBufferObject> depthRenderBufferObjects;
    std::vector<Paint> paints;

    textures.reserve(NUM_PASSES * 2);
    depthRenderBufferObjects.reserve(NUM_PASSES);
    paints.reserve(NUM_PASSES);

    for (int i = 0; i < NUM_PASSES; ++i) {
        textures.emplace_back(width, height, glTexture2D::TextureFormat::RGBA8, nullptr);
        textures.emplace_back(width, height, glTexture2D::TextureFormat::R32, nullptr);
        depthRenderBufferObjects.emplace_back(width, height, glRenderBuffer::RenderBufferFormat::D24S8);

        paints.emplace_back(
            std::vector<Texture*> { &textures[i * 2], &textures[i * 2 + 1] }
            , std::vector<RenderBufferObject*> { &depthRenderBufferObjects[i] }
        );
        paints[i].build();
    }

    Paint& screenPaint = Paint::getScreenPaint();

    VertexShader commonVertexShader = VertexShader("../../example/alphaBlend/scene.vs.glsl");
    FragmentShader commonFragmentShader = FragmentShader("../../example/alphaBlend/scene.fs.glsl");
    VertexShader quadVertexShader = VertexShader("../../example/alphaBlend/quad.vs.glsl");
    FragmentShader quadFragmentShader = FragmentShader("../../example/alphaBlend/quad.fs.glsl");

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

        for (int i = 0; i < NUM_PASSES; ++i) {
            if (i == 0) {
                commonShader.setUniform("enableComparison", 0);
            } else {
                commonShader.setUniform("enableComparison", 1);
            }

            paints[i].use([&structuredRenderUnit, &commonShader, &paints, i](RenderContext& ctx) {
                ctx.clear(Vec4f { 0.0, 0.0, 0.0, 0.5 });

                ctx.configureDepthTest(
                    glDepthTestConfigurer::DepthTestStatus::ENABLE_TEST
                    | glDepthTestConfigurer::DepthTestStatus::ENABLE_MASK
                    , glDepthTestConfigurer::DepthFunc::LESS);

                ctx.disableAlphaTest();

                if (i > 0) {
                    structuredRenderUnit->draw([&commonShader, &paints, i](RenderUnit* renderUnit) {
                        auto numTextures = renderUnit->getNumTextures();
                        commonShader.setTexture(numTextures, "previousColorTexture", paints[i - 1].getColorTexture(0));
                        commonShader.setTexture(numTextures + 1, "previousDepthTexture", paints[i - 1].getColorTexture(1));
                        renderUnit->draw(commonShader);
                    });
                } else {
                    structuredRenderUnit->draw([&commonShader](RenderUnit* renderUnit) {
                        renderUnit->draw(commonShader);
                    });
                }
            });
        }

        for (int i = 0; i < NUM_PASSES; ++i) {
            quadShader.setTexture(i, "colorTexture" + std::to_string(i), paints[i].getColorTexture(0));
        }

        screenPaint.use([&quadShader, &quadRenderUnit](RenderContext& ctx) {
            quadShader.setUniform("numPasses", NUM_PASSES);
            ctx.disableDepthTest();
            ctx.clear(Vec4f { 0.0, 0.0, 0.0, 1.0 });
            quadRenderUnit.draw(quadShader);
        });

        windowContext.swapBuffers();
        windowContext.pollEvents();
    }

    return 0;
}
