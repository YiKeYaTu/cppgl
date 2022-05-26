//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_CPPGL_HPP
#define CPPGL_CPPGL_HPP

#include <core/window/WindowContext.hpp>
#include "core/paint/DrawUnit.hpp"
#include <core/shader/ShaderProgram.hpp>
#include <math/Vec.hpp>

#ifndef CPPGL_GLFW_CONTEXT_VERSION_MAJOR
#define CPPGL_GLFW_CONTEXT_VERSION_MAJOR 3
#endif

#ifndef CPPGL_GLFW_CONTEXT_VERSION_MINOR
#define CPPGL_GLFW_CONTEXT_VERSION_MINOR 3
#endif

class CppGL {
private:
    void _configureOpenGL() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CPPGL_GLFW_CONTEXT_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CPPGL_GLFW_CONTEXT_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }
public:
    CppGL() {
        _configureOpenGL();
    }

    void clear(const Vec4f& color, int f = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
        glClearColor(color.x(), color.y(), color.z(), color.w());
        glClear(f);
    }

    void drawTriangle(DrawUnit& drawUnit, ShaderProgram& program) {
        drawUnit.use();
        program.use();

        if (drawUnit._ebo) {
            glDrawElements(GL_TRIANGLES, drawUnit._eboData->size(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, drawUnit._vboData->size());
        }
    }
};

#endif //CPPGL_CPPGL_HPP
