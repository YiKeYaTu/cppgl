//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_TRIANGLERENDERUNIT_HPP
#define CPPGL_TRIANGLERENDERUNIT_HPP

#include "RenderUnit.hpp"
#include "core/shader/ShaderProgram.hpp"

class TriangleRenderUnit: public RenderUnit {
public:
    using RenderUnit::RenderUnit;

    void draw(ShaderProgram &shaderProgram) override {
        requireBuilt()
        shaderProgram.use();
        if (_eboData) {
            gl::draw::drawTriangles(_eboData->size());
        } else {
            gl::draw::drawTriangles(0, _vboData->size());
        }
    }
};

#endif //CPPGL_TRIANGLERENDERUNIT_HPP
