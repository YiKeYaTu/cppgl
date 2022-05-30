//
// Created by lc on 2022/5/30.
//

#ifndef CPPGL_WINDOWSTATE_HPP
#define CPPGL_WINDOWSTATE_HPP

#include <iostream>
#include <string>
#include <core/gl/configurer/glWindowConfigurer.hpp>
#include <core/context/state/MouseState.hpp>
#include <core/context/state/KeyboardState.hpp>

struct WindowState {
public:
    std::string title;

    unsigned int viewportWidth;
    unsigned int viewportHeight;

    MouseState mouseState;
    KeyboardState keyboardState;

    WindowState(unsigned int viewportWidth, unsigned int viewportHeight, std::string title)
        : viewportWidth(viewportWidth), viewportHeight(viewportHeight), title(title)  {}

    static WindowState& getWindowState(GLFWwindow* window) {
        return *(static_cast<WindowState*>(glfwGetWindowUserPointer(window)));
    }

    void updateState(GLFWwindow* window) {
        mouseState._updateState(window);
        keyboardState._updateState(window);
    }

    static void _framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        auto& windowState = getWindowState(window);
        windowState.viewportWidth = width;
        windowState.viewportHeight = height;
        glViewport(0, 0, width, height);
    }
};

#endif //CPPGL_WINDOWSTATE_HPP
