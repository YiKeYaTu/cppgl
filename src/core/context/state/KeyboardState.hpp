//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_KEYBOARDSTATE_HPP
#define CPPGL_KEYBOARDSTATE_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowState;

enum Keyboard {
    W = GLFW_KEY_W,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    A = GLFW_KEY_A
};

struct KeyboardState {
    friend WindowState;
public:
    bool isKeyPressed(int key) const {
        return glfwGetKey(_window, key) == GLFW_PRESS;
    }

    bool isKeyReleased(int key) const {
        return glfwGetKey(_window, key) == GLFW_RELEASE;
    }

private:
    GLFWwindow* _window = nullptr;

    void _updateState(GLFWwindow* window) {
        _window = window;
    }
};

#endif //CPPGL_KEYBOARDSTATE_HPP
