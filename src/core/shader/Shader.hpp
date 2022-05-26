//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_SHADER_HPP
#define CPPGL_SHADER_HPP

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/xxable/Buildable.hpp>

class ShaderProgram;

class Shader: public Buildable {
    friend ShaderProgram;
private:
    GLuint _handle;
    GLenum _shaderType;
    std::string _shaderSourceString;

    const std::string _loadShaderSource(const std::string& shaderSourcePath) {
        std::ifstream ifs(shaderSourcePath);
        if (!ifs.is_open()) {
            throw std::runtime_error(std::string("ERROR::SHADER::LOADING_FAILED: ") + shaderSourcePath);
        }
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    void _build() override {
        _handle = glCreateShader(_shaderType);

        const char* p = _shaderSourceString.c_str();
        glShaderSource(_handle, 1, &p, NULL);
        glCompileShader(_handle);

        int success;
        glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);

        if (!success) {
            int errorMsgLen;
            glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &errorMsgLen);

            GLchar* infoLog = new GLchar[errorMsgLen];
            glGetShaderInfoLog(_handle, errorMsgLen, NULL, infoLog);

            std::string errorMsg = "ERROR::SHADER::COMPILATION_FAILED\n" + std::string(infoLog);

            delete[] infoLog;
            throw std::runtime_error(errorMsg);
        }
    }

    void _del() {
        glDeleteShader(_handle);
    }

public:
    Shader(const std::string& shaderSourcePath, GLenum shaderType): _shaderType(shaderType) {
        _shaderSourceString = _loadShaderSource(shaderSourcePath);
    }

    ~Shader() {
        _del();
    }
};

#endif //CPPGL_SHADER_HPP
