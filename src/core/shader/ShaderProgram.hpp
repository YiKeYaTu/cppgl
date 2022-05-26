//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_SHADERPROGRAM_HPP
#define CPPGL_SHADERPROGRAM_HPP

#include <math/Mat.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/shader/VertexShader.hpp>
#include <core/shader/FragmentShader.hpp>
#include <core/shader/GeometryShader.hpp>
#include <core/xxable/Usable.hpp>
#include <core/xxable/Buildable.hpp>
#include <core/texture/Texture.hpp>
#include <macro/debug.hpp>

class ShaderProgram: public Usable, public Buildable {
private:
    GLuint _handle;
    VertexShader* _vertexShader;
    FragmentShader* _fragmentShader;
    GeometryShader* _geometryShader;

    void _build() override {
        _handle = glCreateProgram();

        _vertexShader->build();
        _fragmentShader->build();

        glAttachShader(_handle, _vertexShader->_handle);
        if (_geometryShader) {
            glAttachShader(_handle, _geometryShader->_handle);
        }
        glAttachShader(_handle, _fragmentShader->_handle);
        glLinkProgram(_handle);
    }
public:
    ShaderProgram(VertexShader* vertexShader, FragmentShader* fragmentShader, GeometryShader* geometryShader = NULL)
        : _vertexShader(vertexShader), _fragmentShader(fragmentShader), _geometryShader(geometryShader) {
        assert(_vertexShader != NULL);
        assert(_fragmentShader != NULL);
    }

    virtual void use() override {
        requireBuilt()
        glUseProgram(_handle);
    }

    void setTexture(unsigned int textureUnit, const std::string& name, Texture& texture) {
        use();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        texture.use();
        glUniform1i(glGetUniformLocation(_handle, name.c_str()), textureUnit);
    }

    void setUniform(const std::string& name, const Mat4f& m) {
        use();
        glUniformMatrix4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, m.data());
    }
};

#endif //CPPGL_SHADERPROGRAM_HPP
