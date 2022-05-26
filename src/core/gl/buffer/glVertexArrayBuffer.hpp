//
// Created by lc on 2022/5/7.
//

#ifndef CPPGL_GLVERTEXARRAYBUFFER_HPP
#define CPPGL_GLVERTEXARRAYBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glVertexArrayBuffer {
    GLuint gen() {
        requireWindowContext()
        GLuint handle;
        glGenVertexArrays(1, &handle);
        return handle;
    }

    void bind(GLuint handle) {
        requireWindowContext()
        glBindVertexArray(handle);
    }

    void setData(GLuint index,
                             GLint size,
                             GLenum type,
                             GLboolean normalized,
                             GLsizei stride,
                             const void* pointer) {
        requireWindowContext()
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void del(const GLuint* handle) {
        glDeleteVertexArrays(1, handle);
    }
}

#endif //CPPGL_GLVERTEXARRAYBUFFER_HPP
