//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_WINDOWCONTEXT_HPP
#define CPPGL_WINDOWCONTEXT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/xxable/Usable.hpp>
#include <core/xxable/Buildable.hpp>
#include <core/context/OpenGLContext.hpp>
#include <core/context/state/WindowState.hpp>
#include <core/context/state/MouseState.hpp>
#include <core/context/state/KeyboardState.hpp>
#include <macro/debug.hpp>

class WindowContext: public Usable, public Buildable {
private:
    GLFWwindow* _windowInstance;
    WindowState _windowState;

    void _build() override {
        OpenGLContext::use();

        _windowInstance = glfwCreateWindow(
            _windowState.viewportWidth
            , _windowState.viewportHeight
            , _windowState.title.c_str()
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

        glfwSetWindowUserPointer(_windowInstance, &this->_windowState);
        glfwSetFramebufferSizeCallback(_windowInstance, _windowState._framebufferSizeCallback);
        glfwSetInputMode(_windowInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

public:
    WindowContext(unsigned int width, unsigned int height, const std::string& title)
        : _windowState(
#ifdef __APPLE__
            width / 2
#else
            width
#endif
            ,
#ifdef __APPLE__
            height / 2
#else
            height
#endif
            , title
        ) {}
    void use() override {
        requireBuilt()
        glfwMakeContextCurrent(_windowInstance);
    }

    const WindowState& updateState() {
        _windowState.updateState(_windowInstance);
        return _windowState;
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


#endif //CPPGL_WINDOWCONTEXT_HPP
