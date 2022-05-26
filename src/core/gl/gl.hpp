//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_GL_HPP
#define CPPGL_GL_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/glDraw.hpp>
#include <core/gl/glStatus.hpp>

namespace gl {
    namespace draw {
        using ::glDraw::clear;
        using ::glDraw::drawTriangles;
    }

    namespace status {
        using ::glStatus::isFrameBufferReady;
    }

    unsigned int getCurrentDrawFrameBuffer() {
        GLint fbo = 0;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fbo);
        return fbo;
    }
}

#endif //CPPGL_GL_HPP
