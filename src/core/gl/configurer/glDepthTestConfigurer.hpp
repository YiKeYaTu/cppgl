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
        LEQUAL = GL_LEQUAL,
        LESS = GL_LESS,
        ALWAYS = GL_ALWAYS
    };

    enum DepthTestStatus {
        DEPTH_TEST = 1 << 0,
        DEPTH_MASK = 1 << 1
    };

    void configure(unsigned int depthTestStatus, DepthFunc depthFunc) {
        if (depthTestStatus & DEPTH_TEST) {
            glEnable(GL_DEPTH_TEST);

            if (depthTestStatus & DEPTH_MASK) {
                glDepthMask(GL_TRUE);
            } else {
                glDepthMask(GL_FALSE);
            }

            glDepthFunc(depthFunc);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }
}

#endif //CPPGL_GLDEPTHTESTCONFIGURER_HPP
