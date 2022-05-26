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
        RGBA8,
    };

    enum TextureParameter {
        MIN_FILTER_LINEAR = 0x01,
        MAG_FILTER_LINEAR = 0x02,
    };

    GLuint gen() {
        requireWindowContext()
        unsigned int texture;
        glGenTextures(1, &texture);
        return texture;
    }

    void bind(GLuint texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void del(const GLuint* textures) {
        glDeleteTextures(1, textures);
    }

    void setParameter(unsigned int textureParameter) {
        if (textureParameter & TextureParameter::MIN_FILTER_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        if (textureParameter & TextureParameter::MAG_FILTER_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }

    void asTexture(GLsizei width, GLsizei height, TextureFormat textureFormat, void* data = nullptr) {
        switch (textureFormat) {
            case TextureFormat::RGBA8:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            default:
                throw std::runtime_error("Incorrect format type of texture: " + std::to_string(textureFormat));
        }
    }

    GLuint asColorAttachment(GLuint attachmentID, GLuint texture) {
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
