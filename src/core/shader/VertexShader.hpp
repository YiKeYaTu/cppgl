//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_VERTEXSHADER_HPP
#define CPPGL_VERTEXSHADER_HPP

#include <core/shader/Shader.hpp>

class VertexShader: public Shader {
public:
    VertexShader(const std::string& shaderSourcePath): Shader(shaderSourcePath, GL_VERTEX_SHADER) {}
};

#endif //CPPGL_VERTEXSHADER_HPP
