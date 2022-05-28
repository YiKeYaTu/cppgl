//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_WINDOWCONTEXT_HPP
#define CPPGL_WINDOWCONTEXT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/xxable/Usable.hpp>
#include <core/xxable/Buildable.hpp>
#include <core/context/WindowContextInfo.hpp>
#include <core/context/OpenGLContext.hpp>
#include <macro/debug.hpp>

class WindowContext: public Usable, public Buildable {
private:
    static int _viewportWidth;
    static int _viewportHeight;

    static float _xpos;
    static float _ypos;

    static int _pressedKey;

    static void _framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        _viewportWidth = width;
        _viewportHeight = height;
        glViewport(0, 0, width, height);
    }
    static void _mouseCallback(GLFWwindow* window, double xpos, double ypos) {
        _xpos = xpos;
        _ypos = ypos;
    }

    static void _keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            _pressedKey = key;
        } else if (action == GLFW_RELEASE) {
            _pressedKey = -1;
        }
    }

    GLFWwindow* _windowInstance;
    WindowContextInfo _windowContextInfo;

    void _build() override {
        OpenGLContext::use();

        _windowInstance = glfwCreateWindow(
            _windowContextInfo.windowWidth
            , _windowContextInfo.windowHeight
            , _windowContextInfo.windowTitle.c_str()
            , NULL
            , NULL
        );

        if (_windowInstance == NULL) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        use();

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glfwSetInputMode(_windowInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(_windowInstance, _mouseCallback);
        glfwSetFramebufferSizeCallback(_windowInstance, _framebufferSizeCallback);
        glfwSetKeyCallback(_windowInstance, _keyboardCallback);
    }

public:
    WindowContext(unsigned int width, unsigned int height, const std::string& title) {
        _viewportWidth = width;
        _viewportHeight = height;
#ifdef __APPLE__
        width = width / 2;
        height = height / 2;
#endif
        _windowContextInfo.windowWidth = width;
        _windowContextInfo.windowHeight = height;
        _windowContextInfo.windowTitle = title;
    }
    void use() override {
        requireBuilt()
        glfwMakeContextCurrent(_windowInstance);
    }

    std::tuple<unsigned int, unsigned int> getViewportSize() const {
        return { _viewportWidth, _viewportHeight };
    }

    std::tuple<float, float> getMousePos() const {
        return { _xpos, _ypos };
    }

    int getPressedKey() const {
        return _pressedKey;
    }

    bool shouldClose() {
        return glfwWindowShouldClose(_windowInstance);
    }

    void swapBuffers() {
        glfwSwapBuffers(_windowInstance);
    }

    void pollEvents() {
        glfwPollEvents();
    }
};

int WindowContext::_viewportWidth = 0;
int WindowContext::_viewportHeight = 0;

float WindowContext::_xpos = 0;
float WindowContext::_ypos = 0;

int WindowContext::_pressedKey = 0;

#endif //CPPGL_WINDOWCONTEXT_HPP
