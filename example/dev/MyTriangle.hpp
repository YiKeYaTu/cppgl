//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_MYTRIANGLE_HPP
#define CPPGL_MYTRIANGLE_HPP

#include <core/layout/Layout.hpp>

Layout createTriangleLayout() {
    Layout layout;

    layout.add<float>(3);
    layout.add<float>(3);
    layout.build();

    std::cout << layout << std::endl;

    return layout;
};

#endif //CPPGL_MYTRIANGLE_HPP
