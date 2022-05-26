//
// Created by lc on 2022/4/26.
//

#ifndef CPPGL_BUFFEROBJECT_HPP
#define CPPGL_BUFFEROBJECT_HPP

#include <macro/debug.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/xxable/Usable.hpp>
#include <core/xxable/Buildable.hpp>

class BufferObject: public Usable, public Buildable {
protected:
    GLuint _handle = -1;
public:
    BufferObject() = default;
    virtual ~BufferObject() = default;

    BufferObject(BufferObject&) = delete;
    BufferObject& operator=(BufferObject&) = delete;

    BufferObject(BufferObject&&) = delete;
    BufferObject& operator=(BufferObject&&) = delete;
};

#endif //CPPGL_BUFFEROBJECT_HPP
