//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_VBO_HPP
#define CPPGL_VBO_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/buffer/BufferObject.hpp>
#include <core/buffer/VertexArrayObject.hpp>
#include <core/gl/buffer/glVertexBuffer.hpp>

class VertexBufferObject: public BufferObject {
private:
    void _build() override {
        _handle = glVertexBuffer::gen();
    }
    void _destroy() override {
        glVertexBuffer::del(&_handle);
    }

public:
    virtual ~VertexBufferObject() {
        destroy();
    }
    virtual void use() override {
        requireBuilt()
        glVertexBuffer::bind(_handle);
    }

    template<typename T>
    void bindData(std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        use();
        glVertexBuffer::setData(data, usage);
    }
};

#endif //CPPGL_VBO_HPP
