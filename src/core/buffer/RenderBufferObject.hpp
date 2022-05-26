//
// Created by lc on 2022/5/7.
//

#ifndef CPPGL_RENDERBUFFEROBJECT_HPP
#define CPPGL_RENDERBUFFEROBJECT_HPP

#include <core/buffer/BufferObject.hpp>
#include <core/gl/buffer/glRenderBuffer.hpp>

class FramePaint;
class FrameBufferObject;

class RenderBufferObject: public BufferObject {
    friend FrameBufferObject;
private:
    unsigned int _width;
    unsigned int _height;
    glRenderBuffer::RenderBufferFormat _format;

    void _build() override {
        _handle = glRenderBuffer::gen();
        use();
        glRenderBuffer::setData(_width, _height, _format);
    }
    void _destroy() override {
        glRenderBuffer::del(&_handle);
    }

    void _asFrameBufferRenderBuffer() {
        use();
        glRenderBuffer::asFrameBufferRenderBuffer(_format, _handle);
    }

public:
    RenderBufferObject(unsigned int width, unsigned int height, glRenderBuffer::RenderBufferFormat format)
        : _width(width), _height(height), _format(format) {}

    virtual ~RenderBufferObject() {
        destroy();
    }

    virtual void use() override {
        requireBuilt()
        glRenderBuffer::bind(_handle);
    }
};

#endif //CPPGL_RENDERBUFFEROBJECT_HPP
