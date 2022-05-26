//
// Created by lc on 2022/5/5.
//

#ifndef CPPGL_SCREENPAINT_HPP
#define CPPGL_SCREENPAINT_HPP

#include <core/gl/buffer/glFrameBuffer.hpp>
#include <core/xxable/Usable.hpp>
#include <macro/debug.hpp>

#ifdef CPPGL_DEBUG_MODE
#define checkCurrentDrawFrameBuffer() \
    if (0 != gl::getCurrentDrawFrameBuffer()) { \
        throw std::runtime_error("Current binding framebuffer is not matched"); \
    }
#else
#define checkCurrentDrawFrameBuffer()
#endif

class ScreenPaint: public Usable {
private:
    ScreenPaint() = default;

    ScreenPaint(ScreenPaint&) = delete;
    ScreenPaint& operator=(ScreenPaint&) = delete;

public:
    static ScreenPaint& getScreenPaint() {
        static ScreenPaint screenPaint;
        return screenPaint;
    }

    void use() override {
        glFrameBuffer::bind(0);
    }

    void clear(const Vec4f& color, int f = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
        checkCurrentDrawFrameBuffer()
        gl::draw::clear(color, f);
    }

    void draw(RenderUnit& drawUnit, ShaderProgram& shaderProgram) {
        checkCurrentDrawFrameBuffer()
        drawUnit.use();
        drawUnit.draw(shaderProgram);
    }
};

#endif //CPPGL_SCREENPAINT_HPP
