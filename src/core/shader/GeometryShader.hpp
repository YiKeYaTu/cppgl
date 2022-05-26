//
// Created by lc on 2022/4/26.
//

#ifndef CPPGL_GEOMETRYSHADER_HPP
#define CPPGL_GEOMETRYSHADER_HPP

#include <core/shader/Shader.hpp>

class GeometryShader: public Shader {
public:
    GeometryShader(const std::string& shaderSourcePath): Shader(shaderSourcePath, GL_GEOMETRY_SHADER) {}
};

#endif //CPPGL_GEOMETRYSHADER_HPP
