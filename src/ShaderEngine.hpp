//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_SHADERENGINE_HPP
#define CPPGL_SHADERENGINE_HPP

#include <unordered_map>
#include <core/shader/VertexShader.hpp>
#include <core/shader/FragmentShader.hpp>
#include <core/shader/GeometryShader.hpp>
#include <core/shader/ShaderProgram.hpp>

class ShaderEngine {
private:
    std::unordered_map<std::string, std::shared_ptr<VertexShader>> vertexShaderMap;
    std::unordered_map<std::string, std::shared_ptr<FragmentShader>> fragmentShaderMap;
    std::unordered_map<std::string, std::shared_ptr<GeometryShader>> geometryShaderMap;
public:
    ShaderEngine() {}

    std::shared_ptr<VertexShader> loadVertexShader(const std::string& vs) {
        if (vertexShaderMap.count(vs) == 0) {
            vertexShaderMap.insert({ vs, std::make_shared<VertexShader>(vs) });
        }
        return vertexShaderMap[vs];
    }

    std::shared_ptr<FragmentShader> loadFragmentShader(const std::string& fs) {
        if (fragmentShaderMap.count(fs) == 0) {
            fragmentShaderMap.insert({ fs, std::make_shared<FragmentShader>(fs) });
        }
        return fragmentShaderMap[fs];
    }

    std::shared_ptr<GeometryShader> loadGeometryShader(const std::string& gs) {
        if (geometryShaderMap.count(gs) == 0) {
            geometryShaderMap.insert({ gs, std::make_shared<GeometryShader>(gs) });
        }
        return geometryShaderMap[gs];
    }

    std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& vs, const std::string& fs) {
        std::shared_ptr<VertexShader> vertexShader = loadVertexShader(vs);
        std::shared_ptr<FragmentShader> fragmentShader = loadFragmentShader(fs);
        auto program = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);
        program->build();

        return program;
    }

    std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& vs, const std::string& fs, const std::string& gs) {
        std::shared_ptr<VertexShader> vertexShader = loadVertexShader(vs);
        std::shared_ptr<FragmentShader> fragmentShader = loadFragmentShader(fs);
        std::shared_ptr<GeometryShader> geometryShader = loadGeometryShader(gs);
        auto program = std::make_shared<ShaderProgram>(vertexShader, fragmentShader, geometryShader);
        program->build();

        return program;
    }

    void deleteVertexShader(const std::string& name) {
        if (vertexShaderMap.count(name) > 0) {
            vertexShaderMap.erase(name);
        }
    }

    void deleteFragmentShader(const std::string& name) {
        if (fragmentShaderMap.count(name) > 0) {
            fragmentShaderMap.erase(name);
        }
    }

    void deleteGeometryShader(const std::string& name) {
        if (geometryShaderMap.count(name) > 0) {
            geometryShaderMap.erase(name);
        }
    }
};

#endif //CPPGL_SHADERENGINE_HPP
