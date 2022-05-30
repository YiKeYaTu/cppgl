//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_WINDOWCONTEXTINFO_HPP
#define CPPGL_WINDOWCONTEXTINFO_HPP

#include <string>
#include <core/context/state/KeyboardState.hpp>
#include <core/context/state/MouseState.hpp>

struct WindowContextInfo {
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::string windowTitle;

    KeyboardState keyboardState;
    MouseState mouseState;
};

#endif //CPPGL_WINDOWCONTEXTINFO_HPP
