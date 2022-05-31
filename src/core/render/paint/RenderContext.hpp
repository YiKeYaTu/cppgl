//
// Created by lc on 2022/5/30.
//

#ifndef CPPGL_RENDERCONTEXT_HPP
#define CPPGL_RENDERCONTEXT_HPP

#include <core/gl/glDraw.hpp>
#include <core/gl/configurer/glDepthTestConfigurer.hpp>
#include <core/gl/configurer/glAlphaTestConfigurer.hpp>
#include <core/render/renderUnit/RenderUnit.hpp>
#include <core/shader/ShaderProgram.hpp>

class Paint;
class RenderContext {
    friend Paint;
private:
    RenderContext() {}
public:
    void clear(const Vec4f& color, int f = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
        glDraw::clear(color, f);
    }

    void configureDepthTest(unsigned int depthTestStatus, glDepthTestConfigurer::DepthFunc depthFunc) {
        glDepthTestConfigurer::configure(depthTestStatus, depthFunc);
    }

    void disableDepthTest() {
        glDepthTestConfigurer::configure(glDepthTestConfigurer::DepthTestStatus::DISABLE_TEST);
    }

    void configureAlphaTest(unsigned int alphaTestStatus, glAlphaTestConfigurer::BlendFunc sfactor, glAlphaTestConfigurer::BlendFunc dfactor) {
        glAlphaTestConfigurer::configure(alphaTestStatus, sfactor, dfactor);
    }

    void disableAlphaTest() {
        glAlphaTestConfigurer::configure(glAlphaTestConfigurer::AlphaTestStatus::DISABLE_TEST);
    }

    void draw(RenderUnit& drawUnit, ShaderProgram& shaderProgram) {
        shaderProgram.use();
        drawUnit.use();
        drawUnit.draw(shaderProgram);
    }
};

#endif //CPPGL_RENDERCONTEXT_HPP
