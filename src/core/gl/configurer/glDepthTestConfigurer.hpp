//
// Created by lc on 2022/5/17.
//

#ifndef CPPGL_GLDEPTHTESTCONFIGURER_HPP
#define CPPGL_GLDEPTHTESTCONFIGURER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/macro.hpp>

namespace glDepthTestConfigurer {
    enum DepthFunc {
        EQUAL = GL_EQUAL,
        NOTEQUAL = GL_NOTEQUAL,
        GEQUAL = GL_GEQUAL,
        LEQUAL = GL_LEQUAL,
        LESS = GL_LESS,
        ALWAYS = GL_ALWAYS,
        GREATER = GL_GREATER,
        NEVER = GL_NEVER,
    };

    enum DepthTestStatus {
        DISABLE_TEST = 0,
        ENABLE_TEST = 1 << 0,
        ENABLE_MASK = 1 << 1
    };

    void configure(unsigned int depthTestStatus, DepthFunc depthFunc = DepthFunc::LESS) {
        requireWindowContext()
        if (depthTestStatus == DISABLE_TEST) {
            glDisable(GL_DEPTH_TEST);
//            glDepthMask(GL_TRUE);
        } else {
            glEnable(GL_DEPTH_TEST);

            if (depthTestStatus & ENABLE_MASK) {
                glDepthMask(GL_TRUE);
            } else {
                glDepthMask(GL_FALSE);
            }

            glDepthFunc(depthFunc);
        }
    }
}

#endif //CPPGL_GLDEPTHTESTCONFIGURER_HPP
