//
// Created by lc on 2022/5/24.
//

#ifndef CPPGL_STRUCTUREDRENDERUNITLOADER_HPP
#define CPPGL_STRUCTUREDRENDERUNITLOADER_HPP

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <core/render/renderUnit/StructuredRenderUnit.hpp>
#include <core/render/renderUnit/TriangleRenderUnit.hpp>
#include <core/layout/Layout.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class StructuredRenderUnitLoader {
private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
    const std::string _root;
    const aiScene* _scene;
    Layout* _layout;
public:
    StructuredRenderUnitLoader(const std::string root, const aiScene* scene, Layout* layout)
        : _root(root), _scene(scene), _layout(layout) {}

    std::shared_ptr<StructuredRenderUnit> processScene() {
        if (_scene->HasMaterials()) {
            for (int i = 0; i < _scene->mNumMaterials; i++) {
                preloadTextures(_scene->mMaterials[i]);
            }
        }

        std::shared_ptr<StructuredRenderUnit> structuredRenderUnit = processNode(_scene->mRootNode);
        return structuredRenderUnit;
    }

    std::shared_ptr<StructuredRenderUnit> processNode(aiNode* node) {
        std::vector<std::shared_ptr<StructuredRenderUnit>> children;
        std::vector<std::shared_ptr<RenderUnit>> renderUnits;
        children.reserve(node->mNumChildren);
        renderUnits.reserve(node->mNumMeshes);

        for (int i = 0; i < node->mNumChildren; ++i) {
            children.push_back(processNode(node->mChildren[i]));
        }

        for (int i = 0; i < node->mNumMeshes; ++i) {
            renderUnits.push_back(processMesh(_scene->mMeshes[node->mMeshes[i]]));
        }

        std::shared_ptr<StructuredRenderUnit> structuredRenderUnit = std::make_shared<StructuredRenderUnit>(renderUnits, children);

        return structuredRenderUnit;
    }
    std::shared_ptr<RenderUnit> processMesh(aiMesh* mesh) {
        if (mesh->mPrimitiveTypes & aiPrimitiveType::aiPrimitiveType_TRIANGLE) {
            std::shared_ptr<std::vector<unsigned int>> ebo = std::make_shared<std::vector<unsigned int>>();
            ebo->reserve(mesh->mNumFaces * mesh->mFaces->mNumIndices);
            for (int i = 0; i < mesh->mNumFaces; ++i) {
                for (int j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
                    ebo->push_back(mesh->mFaces[i].mIndices[j]);
                }
            }

            auto textures = processMaterial(_scene->mMaterials[mesh->mMaterialIndex]);

            std::shared_ptr<std::vector<float>> vbo = std::make_shared<std::vector<float>>();
            vbo->reserve(mesh->mNumVertices * _layout->getNumItems());
            for (int i = 0; i < mesh->mNumVertices; ++i) {
                vbo->push_back(mesh->mVertices[i].x);
                vbo->push_back(mesh->mVertices[i].y);
                vbo->push_back(mesh->mVertices[i].z);
                vbo->push_back(mesh->mNormals[i].x);
                vbo->push_back(mesh->mNormals[i].y);
                vbo->push_back(mesh->mNormals[i].z);
                vbo->push_back(mesh->mTextureCoords[0][i].x);
                vbo->push_back(mesh->mTextureCoords[0][i].y);
            }

            return std::make_shared<TriangleRenderUnit>(_layout, vbo, ebo, textures);
        } else {
            throw std::runtime_error("unknown primitive type");
        }
    }

    std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>> processMaterial(aiMaterial* mat) {
        std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>> map;
        map.insert(std::pair<std::string, std::vector<std::shared_ptr<Texture>>>("diffuseTexture", loadTextures(mat, aiTextureType_DIFFUSE)));
        map.insert(std::pair<std::string, std::vector<std::shared_ptr<Texture>>>("ambientTexture", loadTextures(mat, aiTextureType_AMBIENT)));
        map.insert(std::pair<std::string, std::vector<std::shared_ptr<Texture>>>("heightTexture", loadTextures(mat, aiTextureType_HEIGHT)));
        return map;
    }

    void preloadTextures(aiMaterial* mat) {
        loadTextures(mat, aiTextureType_DIFFUSE);
    }

    std::vector<std::shared_ptr<Texture>> loadTextures(aiMaterial* mat, aiTextureType type) {
        std::vector<std::shared_ptr<Texture>> textures;

        for (int i = 0; i < mat->GetTextureCount(type); ++ i) {
            aiString str; mat->GetTexture(type, i, &str);
            std::string filename = _root + "/" + str.data;

            if (_textures.count(filename) == 0) {
                int width, height, nrComponents;
                unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

                if (!data) {
                    throw std::runtime_error("failed to load texture: " + filename);
                }

                glTexture2D::TextureFormat format;
                switch (nrComponents) {
                    case 1:
                        format = glTexture2D::R8;
                        break;
                    case 3:
                        format = glTexture2D::RGB8;
                        break;
                    case 4:
                        format = glTexture2D::RGBA8;
                        break;
                    default:
                        throw std::runtime_error("unknown texture format with: " + std::to_string(nrComponents) + "channel");
                }

                _textures[_root + str.data] = std::make_shared<Texture2D>(
                    width
                    , height
                    , format
                    , data
                    , glTexture2D::TextureParameter::MIN_FILTER_LINEAR_MIP_LINEAR
                    | glTexture2D::TextureParameter::MAG_FILTER_LINEAR
                    | glTexture2D::TextureParameter::WRAP_S_REPEAT
                    | glTexture2D::TextureParameter::WRAP_T_REPEAT
                    , true
                );
                _textures[_root + str.data]->build();
                stbi_image_free(data);
            }

            textures.push_back(_textures[_root + str.data]);
        }
        return textures;
    }

    static Layout createLayout() {
        Layout layout;
        layout.add<float>(3); // vertex
        layout.add<float>(3); // normal
        layout.add<float>(2); // tex coords
        layout.build();
        return layout;
    }

    static std::shared_ptr<StructuredRenderUnit> load(const std::string& filePath) {
        static Assimp::Importer importer;
        static Layout layout = createLayout();

        const aiScene* scene = importer.ReadFile(
            filePath
            , aiProcess_GenNormals
            | aiProcess_Triangulate
            | aiProcess_CalcTangentSpace
        );

        StructuredRenderUnitLoader structuredRenderUnitLoader = StructuredRenderUnitLoader(
            filePath.substr(
                0
                , filePath.find_last_of('/'))
                , scene
                , &layout
            );

        return structuredRenderUnitLoader.processScene();
    }
};

#endif //CPPGL_STRUCTUREDRENDERUNITLOADER_HPP
