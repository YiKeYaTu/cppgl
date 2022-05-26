//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_ElementBufferObject_HPP
#define CPPGL_ElementBufferObject_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/buffer/BufferObject.hpp>
#include <core/gl/buffer/glElementBuffer.hpp>

class ElementBufferObject: public BufferObject {
private:
    void _build() override {
        _handle = glElementBuffer::gen();
    }

    void _destroy() override {
        glElementBuffer::del(&_handle);
    }

public:
    virtual ~ElementBufferObject() {
        destroy();
    }

    virtual void use() override {
        requireBuilt()
        glElementBuffer::bind(_handle);
    }

    void bindData(std::vector<unsigned int>& data, GLenum usage = GL_STATIC_DRAW) {
        use();
        glElementBuffer::setData(data, usage);
    }
};

#endif //CPPGL_ElementBufferObject_HPP
