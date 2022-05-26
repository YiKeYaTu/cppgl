//
// Created by lc on 2022/5/6.
//

#ifndef CPPGL_GLSTATUS_HPP
#define CPPGL_GLSTATUS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glStatus {
    bool isFrameBufferReady() {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }
}

#endif //CPPGL_GLSTATUS_HPP
