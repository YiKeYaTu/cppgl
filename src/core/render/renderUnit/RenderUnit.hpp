//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_RENDERUNIT_HPP
#define CPPGL_RENDERUNIT_HPP

#include <core/xxable/Buildable.hpp>
#include <core/xxable/Usable.hpp>
#include <core/layout/Layout.hpp>
#include <core/buffer/VertexBufferObject.hpp>
#include <core/buffer/VertexArrayObject.hpp>
#include <core/buffer/ElementBufferObject.hpp>
#include <core/shader/ShaderProgram.hpp>
#include <core/render/renderUnit/material/Material.hpp>

class FramePaint;

class RenderUnit: public Buildable, public Usable {
    friend FramePaint;

protected:
    Layout* _layout;
    std::vector<float>* _vboData;
    std::vector<unsigned int>* _eboData;

    Material* _material;

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

        for (const auto &item: _layout->_layoutItems) {
            _vao.setVertexAttribPointer(item.location, item.size, item.type, item.normalized, item.stride, (void*) item.offset);
        }
    }

public:
    RenderUnit(
        Layout* layout,
        std::vector<float>* vboData,
        std::vector<unsigned int>* eboData = nullptr,
        Material* material = nullptr
    ): _layout(layout), _vboData(vboData), _eboData(eboData), _material(material) {}

    void use() override {
        build();
        _vao.use();
    }

    virtual void draw(ShaderProgram& shaderProgram) = 0;
};

#endif //CPPGL_RENDERUNIT_HPP
