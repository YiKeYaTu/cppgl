//
// Created by lc on 2022/5/30.
//

#ifndef CPPGL_QUAD_HPP
#define CPPGL_QUAD_HPP

#include <vector>
#include <core/layout/Layout.hpp>
#include <core/render/renderUnit/TriangleRenderUnit.hpp>

struct Quad {
    std::vector<float> quadVertexes = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    std::vector<unsigned int> quadIndexes = {
        1, 0, 3,
        2, 1, 3
    };

    TriangleRenderUnit asRenderUnit() {
        static Layout layout;

        layout.add<float>(3);
        layout.add<float>(2);
        layout.build();

        return TriangleRenderUnit(&layout, &quadVertexes, &quadIndexes);
    }
};

#endif //CPPGL_QUAD_HPP
