//
// Created by lc on 2022/5/7.
//

#ifndef CPPGL_GLVERTEXBUFFER_HPP
#define CPPGL_GLVERTEXBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glVertexBuffer {
    GLuint gen() {
        requireWindowContext()
        GLuint handle;
        glGenBuffers(1, &handle);
        return handle;
    }

    void bind(GLuint handle) {
        requireWindowContext()
        glBindBuffer(GL_ARRAY_BUFFER, handle);
    }

    template<typename T>
    void setData(std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        requireWindowContext()
        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), usage);
    }

    void del(const GLuint* handle) {
        glDeleteBuffers(1, handle);
    }
}

#endif //CPPGL_GLVERTEXBUFFER_HPP
