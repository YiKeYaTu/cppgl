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

    unsigned int* _data;

    void _build() override {
        _setHandle(glTexture2D::gen());
        glTexture2D::bind(_getHandle());
        glTexture2D::asTexture(_width, _height, _textureFormat, _data);
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
        unsigned int* data = nullptr,
        unsigned long textureParameter = glTexture2D::TextureParameter::MIN_FILTER_LINEAR | glTexture2D::TextureParameter::MAG_FILTER_LINEAR
    ) : _width(width), _height(height), _textureFormat(textureFormat), _data(data), _textureParameter(textureParameter) {}

    void use() override {
        requireBuilt()
        glTexture2D::bind(_getHandle());
    }

    void resize(unsigned int width, unsigned int height) override {
        requireBuilt()
        _width = width;
        _height = height;
        use();
        glTexture2D::asTexture(_width, _height, _textureFormat, _data);
    }

//    static Texture2D* createTexture2D(
//        unsigned int width,
//        unsigned int height,
//        glTexture2D::TextureFormat textureFormat,
//        unsigned long textureParameter = glTexture2D::TextureParameter::MIN_FILTER_LINEAR
//            | glTexture2D::TextureParameter::MAG_FILTER_LINEAR
//    ) {
//        static std::unordered_map<unsigned int, Texture2D> textures;
//        static unsigned int textureGid = 1;
//
//        textures.emplace(
//            std::piecewise_construct,
//            std::forward_as_tuple(textureGid),
//            std::forward_as_tuple(width, height, textureFormat, textureParameter)
//        );
//
//        return &textures.at(textureGid ++);
//    }
};

#endif //CPPGL_TEXTURE2D_HPP
