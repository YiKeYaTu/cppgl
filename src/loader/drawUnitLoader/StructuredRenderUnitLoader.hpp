//
// Created by lc on 2022/5/24.
//

#ifndef CPPGL_STRUCTUREDRENDERUNITLOADER_HPP
#define CPPGL_STRUCTUREDRENDERUNITLOADER_HPP

#include "core/render/renderUnit/StructuredRenderUnit.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class StructuredRenderUnitLoader {
private:
    static void _processScene(const aiScene* scene) {}
    static void _processNode() {}
    static void _processMesh() {}
    static void _processMaterial() {}
public:
    static void load(const std::string& filePath) {
        static Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            filePath
            , aiProcess_GenNormals
            | aiProcess_Triangulate
        );

        _processScene(scene);

    }
};

#endif //CPPGL_STRUCTUREDRENDERUNITLOADER_HPP
