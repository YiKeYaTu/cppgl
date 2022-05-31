//
// Created by lc on 2022/5/30.
//

#ifndef CPPGL_GLALPHATESTCONFIGURER_HPP
#define CPPGL_GLALPHATESTCONFIGURER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glAlphaTestConfigurer {
    enum BlendFunc {
        ZERO = GL_ZERO
        , ONE = GL_ONE
        , SRC_ALPHA = GL_SRC_ALPHA
        , ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA
    };

    enum AlphaTestStatus {
        DISABLE_TEST = 0
        , ENABLE_TEST = 1 << 0
    };

    void configure(unsigned int alphaTestStatus, BlendFunc sfactor = BlendFunc::SRC_ALPHA, BlendFunc dfactor = ONE_MINUS_SRC_ALPHA) {
        requireWindowContext()
        if (alphaTestStatus == DISABLE_TEST) {
            glDisable(GL_BLEND);
        } else {
            glEnable(GL_BLEND);
            glBlendFunc(sfactor, dfactor);
        }
    }
}

#endif //CPPGL_GLALPHATESTCONFIGURER_HPP
