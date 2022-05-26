//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_PAINT_HPP
#define CPPGL_PAINT_HPP

#include <vector>
#include <macro/debug.hpp>
#include <core/shader/ShaderProgram.hpp>
#include <core/buffer/FrameBufferObject.hpp>
#include <core/xxable/Usable.hpp>
#include "core/render/renderUnit/RenderUnit.hpp"
#include <core/texture/Texture.hpp>
#include <core/gl/glDraw.hpp>

#ifdef CPPGL_DEBUG_MODE
#define checkCurrentDrawFrameBuffer() \
    if (_framebufferObject._handle != gl::getCurrentDrawFrameBuffer()) { \
        throw std::runtime_error("Current binding framebuffer is not matched"); \
    }
#else
#define checkCurrentDrawFrameBuffer()
#endif

class FramePaint: public Usable, public Buildable {
private:
    FrameBufferObject _framebufferObject;

    void _build() override {
        _framebufferObject.build();
    }

public:
    FramePaint(
        const std::vector<Texture*>& colorTextures,
        const std::vector<RenderBufferObject*>& renderBufferObjects = {}
    ): _framebufferObject(colorTextures, renderBufferObjects) { }

    Texture& getColorTexture(unsigned int idx) {
        return *_framebufferObject._colorTextures.at(idx);
    }

    void use() override {
        requireBuilt()
        _framebufferObject.use();
    }

    void clear(const Vec4f& color, int f = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
        checkCurrentDrawFrameBuffer()
        glDraw::clear(color, f);
    }

    void draw(RenderUnit& drawUnit, ShaderProgram& shaderProgram) {
        checkCurrentDrawFrameBuffer()
        shaderProgram.use();
        drawUnit.use();
        drawUnit.draw(shaderProgram);
    }
};

#endif //CPPGL_GLDRAW_HPP
