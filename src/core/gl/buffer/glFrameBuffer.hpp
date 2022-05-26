//
// Created by lc on 2022/5/7.
//

#ifndef CPPGL_GLFRAMEBUFFER1_HPP
#define CPPGL_GLFRAMEBUFFER1_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glFrameBuffer {
    GLuint gen() {
        requireWindowContext()
        GLuint handle;
        glGenFramebuffers(1, &handle);
        return handle;
    }

    void bind(GLuint handle) {
        requireWindowContext()
        glBindFramebuffer(GL_FRAMEBUFFER, handle);
    }

    void del(GLuint* handle) {
        requireWindowContext()
        glDeleteFramebuffers(1, handle);
    }
}

#endif //CPPGL_GLFRAMEBUFFER1_HPP
