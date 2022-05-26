//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_OPENGLCONTEXT_HPP
#define CPPGL_OPENGLCONTEXT_HPP

#include <macro/version.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLContext {
private:
    OpenGLContext() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CPPGL_GLFW_CONTEXT_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CPPGL_GLFW_CONTEXT_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }
public:
    static void use() {
        static OpenGLContext openGLContext;
    }
};

#endif //CPPGL_OPENGLCONTEXT_HPP
