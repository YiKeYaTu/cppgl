//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_MOUSESTATE_HPP
#define CPPGL_MOUSESTATE_HPP

class WindowState;

struct MouseState {
    friend WindowState;
public:
    double x, y;

private:
    GLFWwindow* _window = nullptr;

    void _updateState(GLFWwindow* window) {
        _window = window;
        glfwGetCursorPos(_window, &x, &y);
    }
};

#endif //CPPGL_MOUSESTATE_HPP
