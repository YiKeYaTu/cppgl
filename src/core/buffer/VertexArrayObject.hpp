//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_VAO_HPP
#define CPPGL_VAO_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/buffer/BufferObject.hpp>
#include <core/gl/gl.hpp>
#include <core/gl/buffer/glVertexArrayBuffer.hpp>
#include <macro/debug.hpp>

class VertexArrayObject: public BufferObject {
private:
    void _build() override {
        _handle = glVertexArrayBuffer::gen();
    }
    void _destroy() override {
        glVertexArrayBuffer::del(&_handle);
    }

public:
    virtual ~VertexArrayObject() {
        destroy();
    }

    virtual void use() override {
        requireBuilt()
        glVertexArrayBuffer::bind(_handle);
    }

    void setVertexAttribPointer(
        GLuint index,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const void* pointer
    ) {
        use();
        glVertexArrayBuffer::setData(index, size, type, normalized, stride, pointer);
    }
};

#endif //CPPGL_VAO_HPP
