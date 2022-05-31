//
// Created by lc on 2022/5/6.
//

#ifndef CPPGL_GLTEXTURE2D_HPP
#define CPPGL_GLTEXTURE2D_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glTexture2D {
    enum TextureFormat {
        RGBA8 = GL_RGBA,
        RGB8 = GL_RGB,
        R8 = GL_RED,
        R32
    };

    enum TextureParameter {
        MIN_FILTER_LINEAR = 0x01 << 0,
        MIN_FILTER_LINEAR_MIP_LINEAR = 0x01 << 1,
        MAG_FILTER_LINEAR = 0x01 << 2,
        WRAP_S_REPEAT = 0x01 << 3,
        WRAP_T_REPEAT = 0x01 << 4
    };

    GLuint gen() {
        requireWindowContext()
        unsigned int texture;
        glGenTextures(1, &texture);
        return texture;
    }

    void bind(GLuint texture) {
        requireWindowContext()
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void del(const GLuint* textures) {
        requireWindowContext()
        glDeleteTextures(1, textures);
    }

    void genMipmap() {
        requireWindowContext()
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void setUnpackAlignment(unsigned int byte) {
        requireWindowContext()
        glPixelStorei(GL_UNPACK_ALIGNMENT, byte);
    }

    void setParameter(unsigned int textureParameter) {
        requireWindowContext()
        if (textureParameter & TextureParameter::MIN_FILTER_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        } else if (textureParameter & MIN_FILTER_LINEAR_MIP_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }

        if (textureParameter & TextureParameter::MAG_FILTER_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        if (textureParameter & TextureParameter::WRAP_S_REPEAT) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        }
        if (textureParameter & TextureParameter::WRAP_T_REPEAT) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
    }

    void asTexture(GLsizei width, GLsizei height, TextureFormat textureFormat, void* data = nullptr) {
        requireWindowContext()
        switch (textureFormat) {
            case TextureFormat::R8:
            case TextureFormat::RGB8:
            case TextureFormat::RGBA8:
                glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
                break;
            case TextureFormat::R32:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_FLOAT, data);
                break;
            default:
                throw std::runtime_error("Incorrect format type of texture: " + std::to_string(textureFormat));
        }

        if (width % 4 != 0 || height % 4 != 0) {
            glTexture2D::setUnpackAlignment(1);
        } else {
            glTexture2D::setUnpackAlignment(4);
        }
    }

    GLuint asColorAttachment(GLuint attachmentID, GLuint texture) {
        requireWindowContext()
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentID, GL_TEXTURE_2D, texture, 0);
        return GL_COLOR_ATTACHMENT0 + attachmentID;
    }

    void asDepthAttachment(GLuint texture) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    }

    void asStencilAttachment(GLuint texture) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    }

    void asDepthStencilAttachment(GLuint texture) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    }

}

#endif //CPPGL_GLTEXTURE2D_HPP
