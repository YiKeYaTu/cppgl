//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_FRAGMENTSHADER_HPP
#define CPPGL_FRAGMENTSHADER_HPP

#include <core/shader/Shader.hpp>

class FragmentShader: public Shader {
public:
    FragmentShader(const std::string& shaderSourcePath): Shader(shaderSourcePath, GL_FRAGMENT_SHADER) {}
};

#endif //CPPGL_FRAGMENTSHADER_HPP
