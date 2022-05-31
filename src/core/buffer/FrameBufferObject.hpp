//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_FRAMEBUFFEROBJECT_HPP
#define CPPGL_FRAMEBUFFEROBJECT_HPP

#include <vector>
#include <core/gl/buffer/glFrameBuffer.hpp>
#include <core/gl/texture/glTexture2D.hpp>
#include <core/buffer/BufferObject.hpp>
#include <core/buffer/RenderBufferObject.hpp>
#include <core/texture/Texture.hpp>
#include <core/gl/glDraw.hpp>

class Paint;

class FrameBufferObject: public BufferObject {
    friend Paint;
private:
    std::vector<Texture*> _colorTextures;
    std::vector<RenderBufferObject*> _renderBufferObjects;
    std::vector<unsigned int> _colorTextureNos;

    void _build() override {
        _handle = glFrameBuffer::gen();
        use();

        _colorTextureNos.reserve(_colorTextures.size());

        for (int i = 0; i < _colorTextures.size(); ++i) {
            _colorTextures[i]->build();
            _colorTextureNos.push_back(_colorTextures[i]->_asColorAttachment(i));
        }

        if (_renderBufferObjects.size() > 0) {
            for (int i = 0; i < _renderBufferObjects.size(); ++i) {
                _renderBufferObjects[i]->build();
                _renderBufferObjects[i]->_asFrameBufferRenderBuffer();
            }
        }
    }
    void _destroy() override {
        glFrameBuffer::del(&_handle);
    }

public:
    FrameBufferObject(
        const std::vector<Texture*>& colorTextures,
        const std::vector<RenderBufferObject*>& renderBufferObjects
    ): _colorTextures(colorTextures), _renderBufferObjects(renderBufferObjects) {}

    virtual ~FrameBufferObject() {
        destroy();
    }

    void use() override {
        requireBuilt()
        glFrameBuffer::bind(_handle);
        if (_colorTextureNos.size() > 0) {
            glDraw::drawBuffers(_colorTextureNos);
        }
    }
};

#endif //CPPGL_FRAMEBUFFEROBJECT_HPP
