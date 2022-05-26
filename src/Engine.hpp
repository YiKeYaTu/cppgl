////
//// Created by lc on 2022/4/27.
////
//
//#ifndef CPPGL_ENGINE_HPP
//#define CPPGL_ENGINE_HPP
//
//#include <unordered_map>
//#include <core/CppGL.hpp>
//
//class Runner;
//
//class Engine: public CppGL, private WindowContext {
//    friend Runner;
//private:
//    std::unordered_map<std::string, std::shared_ptr<VertexShader>> vertexShaderMap;
//    std::unordered_map<std::string, std::shared_ptr<FragmentShader>> fragmentShaderMap;
//    std::unordered_map<std::string, std::shared_ptr<GeometryShader>> geometryShaderMap;
//public:
//    Engine() {}
//
//    void initWindow(unsigned int width, unsigned int height, const std::string& title) {
//        WindowContext::_width = width;
//        WindowContext::_height = height;
//        WindowContext::_title = title;
//        WindowContext::build();
//        WindowContext::use();
//    }
//
//    std::shared_ptr<VertexShader> loadVertexShader(const std::string& vs) {
//        if (vertexShaderMap.count(vs) == 0) {
//            vertexShaderMap.insert({ vs, std::make_shared<VertexShader>(vs) });
//        }
//        return vertexShaderMap[vs];
//    }
//
//    std::shared_ptr<FragmentShader> loadFragmentShader(const std::string& fs) {
//        if (fragmentShaderMap.count(fs) == 0) {
//            fragmentShaderMap.insert({ fs, std::make_shared<FragmentShader>(fs) });
//        }
//        return fragmentShaderMap[fs];
//    }
//
//    std::shared_ptr<GeometryShader> loadGeometryShader(const std::string& gs) {
//        if (geometryShaderMap.count(gs) == 0) {
//            geometryShaderMap.insert({ gs, std::make_shared<GeometryShader>(gs) });
//        }
//        return geometryShaderMap[gs];
//    }
//
//    std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& vs, const std::string& fs) {
//        std::shared_ptr<VertexShader> vertexShader = loadVertexShader(vs);
//        std::shared_ptr<FragmentShader> fragmentShader = loadFragmentShader(fs);
//        auto program = std::make_shared<ShaderProgram>(vertexShader, fragmentShader);
//        program->build();
//
//        return program;
//    }
//
//    std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& vs, const std::string& fs, const std::string& gs) {
//        std::shared_ptr<VertexShader> vertexShader = loadVertexShader(vs);
//        std::shared_ptr<FragmentShader> fragmentShader = loadFragmentShader(fs);
//        std::shared_ptr<GeometryShader> geometryShader = loadGeometryShader(gs);
//        auto program = std::make_shared<ShaderProgram>(vertexShader, fragmentShader, geometryShader);
//        program->build();
//
//        return program;
//    }
//
//    virtual void update() = 0;
//    virtual void initialize() = 0;
//};
//
//#endif //CPPGL_ENGINE_HPP
