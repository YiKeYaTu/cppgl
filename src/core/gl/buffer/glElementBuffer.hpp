//
// Created by lc on 2022/5/7.
//

#ifndef CPPGL_GLELEMENTBUFFER_HPP
#define CPPGL_GLELEMENTBUFFER_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glElementBuffer {
    GLuint gen() {
        requireWindowContext()
        GLuint handle;
        glGenBuffers(1, &handle);
        return handle;
    }

    void bind(GLuint handle) {
        requireWindowContext()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    }

    void setData(std::vector<unsigned int>& data, GLenum usage = GL_STATIC_DRAW) {
        requireWindowContext()
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), data.data(), usage);
    }

    void del(GLuint* buffer) {
        requireWindowContext()
        glDeleteBuffers(1, buffer);
    }
}

#endif //CPPGL_GLELEMENTBUFFER_HPP
