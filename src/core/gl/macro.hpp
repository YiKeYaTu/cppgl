//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_MACRO_HPP
#define CPPGL_MACRO_HPP


#include <macro/debug.hpp>
#include <stdexcept>

#if CPPGL_DEBUG_MODE
#define requireWindowContext() \
if (glfwGetCurrentContext() == NULL) { \
    throw std::runtime_error("OpenGL window context is not specified."); \
}
#else
#define requireWindowContext()
#endif

#endif //CPPGL_MACRO_HPP
