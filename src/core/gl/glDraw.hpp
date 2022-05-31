//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_GLDRAW_HPP
#define CPPGL_GLDRAW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math/Vec.hpp>
#include <core/gl/macro.hpp>

namespace glDraw {
    void clear(const Vec4f& color, int f) {
        requireWindowContext()
        glClearColor(color.x(), color.y(), color.z(), color.w());
        glClear(f);
    }

    void drawTriangles(GLsizei count) {
        requireWindowContext()
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

    void drawTriangles(GLint first, GLsizei count) {
        requireWindowContext()
        glDrawArrays(GL_TRIANGLES, first, count);
    }

    void drawBuffers(std::vector<unsigned int>& buffers) {
        glDrawBuffers(buffers.size(), buffers.data());
    }
}

#endif //CPPGL_GLDRAW_HPP
