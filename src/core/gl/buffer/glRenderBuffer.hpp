//
// Created by lc on 2022/5/7.
//

#ifndef CPPGL_GLRENDERBUFFER_HPP
#define CPPGL_GLRENDERBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glRenderBuffer {
    enum RenderBufferFormat {
        D24S8 = GL_DEPTH24_STENCIL8,
    };

    GLuint gen() {
        requireWindowContext()
        unsigned int handle;
        glGenRenderbuffers(1, &handle);
        return handle;
    }

    void bind(GLuint handle) {
        glBindRenderbuffer(GL_RENDERBUFFER, handle);
    }

    void del(GLuint* handle) {
        glDeleteRenderbuffers(1, handle);
    }

    void setData(unsigned int width, unsigned int height, RenderBufferFormat format) {
        glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
    }

    void asFrameBufferRenderBuffer(RenderBufferFormat format, unsigned int handle) {
        switch (format) {
            case D24S8:
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, handle);
                break;
            default:
                throw std::runtime_error("Incorrect format type of render buffer: " + std::to_string(format));
        }
    }
}

#endif //CPPGL_GLRENDERBUFFER_HPP
