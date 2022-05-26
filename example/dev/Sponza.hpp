//
// Created by lc on 2022/5/24.
//

#ifndef CPPGL_SPONZA_HPP
#define CPPGL_SPONZA_HPP

#include <loader/drawUnitLoader/StructuredRenderUnitLoader.hpp>

class Sponza {
public:
    void load() {
        StructuredRenderUnitLoader::load("../../assets/sponza/sponza.obj");
    }
};

#endif //CPPGL_SPONZA_HPP
