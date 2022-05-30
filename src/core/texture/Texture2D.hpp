//
// Created by lc on 2022/5/6.
//

#ifndef CPPGL_TEXTURE2D_HPP
#define CPPGL_TEXTURE2D_HPP

#include <core/gl/texture/glTexture2D.hpp>
#include <core/texture/Texture.hpp>
#include <unordered_map>

class Texture2D: public Texture {
private:
    unsigned int _width;
    unsigned int _height;
    glTexture2D::TextureFormat _textureFormat;
    unsigned long _textureParameter;
    bool _mipmap;

    std::shared_ptr<unsigned char> _data;

    void _build() override {
        _setHandle(glTexture2D::gen());
        glTexture2D::bind(_getHandle());
        glTexture2D::asTexture(_width, _height, _textureFormat, _data.get());

        if (_mipmap) {
            glTexture2D::genMipmap();
        }

        glTexture2D::setParameter(_textureParameter);
    }

    void _destroy() override {
        glTexture2D::del(&_getHandle());
    }

    GLuint _asColorAttachment(GLuint idx) override {
        use();
        return glTexture2D::asColorAttachment(idx, _getHandle());;
    }

public:
    Texture2D(
        unsigned int width,
        unsigned int height,
        glTexture2D::TextureFormat textureFormat,
        unsigned char* data = nullptr,
        unsigned long textureParameter = glTexture2D::TextureParameter::MIN_FILTER_LINEAR | glTexture2D::TextureParameter::MAG_FILTER_LINEAR,
        bool mipmap = false
    ) : Texture2D(
        width
        , height
        , textureFormat
        , std::shared_ptr<unsigned char>(data, memory::emptyDeleter<unsigned char>)
        , textureParameter
        , mipmap) {}

    Texture2D(
        unsigned int width,
        unsigned int height,
        glTexture2D::TextureFormat textureFormat,
        std::shared_ptr<unsigned char> data = nullptr,
        unsigned long textureParameter = glTexture2D::TextureParameter::MIN_FILTER_LINEAR | glTexture2D::TextureParameter::MAG_FILTER_LINEAR,
        bool mipmap = false
    ) : _width(width), _height(height), _textureFormat(textureFormat), _data(data), _textureParameter(textureParameter), _mipmap(mipmap) {}


    void use() override {
        requireBuilt()
        glTexture2D::bind(_getHandle());
    }

    void resize(unsigned int width, unsigned int height) override {
        requireBuilt()
        _width = width;
        _height = height;
        use();
        glTexture2D::asTexture(_width, _height, _textureFormat, _data.get());
    }
};

#endif //CPPGL_TEXTURE2D_HPP
