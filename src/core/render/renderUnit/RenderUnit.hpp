//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_RENDERUNIT_HPP
#define CPPGL_RENDERUNIT_HPP

#include <unordered_map>
#include <core/xxable/Buildable.hpp>
#include <core/xxable/Usable.hpp>
#include <core/layout/Layout.hpp>
#include <core/buffer/VertexBufferObject.hpp>
#include <core/buffer/VertexArrayObject.hpp>
#include <core/buffer/ElementBufferObject.hpp>
#include <core/shader/ShaderProgram.hpp>
#include <core/texture/Texture.hpp>
#include <util/memory.hpp>

class FramePaint;

class RenderUnit: public Buildable, public Usable {
    friend FramePaint;

protected:
    Layout* _layout;
    std::shared_ptr<std::vector<float>> _vboData;
    std::shared_ptr<std::vector<unsigned int>> _eboData;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>> _textures;

    VertexBufferObject _vbo;
    VertexArrayObject _vao;
    ElementBufferObject _ebo;

private:
    void _build() override {
        _vao.build();
        _vao.use();

        _vbo.build();
        _vbo.bindData(*_vboData);

        if (_eboData != NULL) {
            _ebo.build();
            _ebo.bindData(*_eboData);
        }

        for (const auto& textures : _textures) {
            for (const auto& texture : textures.second) {
                texture->build();
            }
        }

        for (const auto &item: _layout->_layoutItems) {
            _vao.setVertexAttribPointer(item.location, item.size, item.type, item.normalized, item.stride, (void*) item.offset);
        }
    }

public:
    RenderUnit(
        Layout* layout,
        std::shared_ptr<std::vector<float>> vboData,
        std::shared_ptr<std::vector<unsigned int>> eboData = nullptr,
        std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>> textures = std::unordered_map<std::string, std::vector<std::shared_ptr<Texture>>>()
    ): _layout(layout), _vboData(vboData), _eboData(eboData), _textures(textures) {}

    void use() override {
        build();
        _vao.use();
    }

    virtual void draw(ShaderProgram& shaderProgram) = 0;
};

#endif //CPPGL_RENDERUNIT_HPP
