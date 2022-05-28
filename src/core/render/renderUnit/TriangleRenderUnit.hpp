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
        RenderUnit::use();

        unsigned int i = 0, j;
        for (const auto& textures : _textures) {
            j = 0;
            for (const auto& texture : textures.second) {
                shaderProgram.setTexture(i, textures.first + std::to_string(j), *texture);
                ++ i;
                ++ j;
            }
        }

        if (_eboData) {
            gl::draw::drawTriangles(_eboData->size());
        } else {
            gl::draw::drawTriangles(0, _vboData->size());
        }
    }
};

#endif //CPPGL_TRIANGLERENDERUNIT_HPP
