//
// Created by lc on 2022/4/26.
//

#ifndef CPPGL_WINDOWCONTEXT_HPP
#define CPPGL_WINDOWCONTEXT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <core/xxable/Usable.hpp>
#include <core/xxable/Buildable.hpp>
#include <core/state/MouseState.hpp>
#include <core/state/KeyboardState.hpp>

class Engine;

class WindowContext: public Usable, public Buildable {
    friend Engine;
private:
    unsigned int _width;
    unsigned int _height;
    std::string _title;

    GLFWwindow* _window;
    MouseState _mouseState;
    KeyboardState _keyboardState;

    void _build() override {
        _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
        if (_window == NULL) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(_window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

public:
    void use() override {
        if (glfwGetCurrentContext() != _window) {
            glfwMakeContextCurrent(_window);
        }
    }

    bool shouldClose() {
        return glfwWindowShouldClose(_window);
    }

    void swapBuffers() {
        glfwSwapBuffers(_window);
    }

    void pollEvents() {
        glfwPollEvents();
    }
};

#endif //CPPGL_WINDOWCONTEXT_HPP
