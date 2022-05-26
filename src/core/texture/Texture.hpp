//
// Created by lc on 2022/5/6.
//

#ifndef CPPGL_TEXTURE_HPP
#define CPPGL_TEXTURE_HPP

#include <core/xxable/Usable.hpp>
#include <core/xxable/Buildable.hpp>

class FramePaint;
class FrameBufferObject;

class Texture: public Usable, public Buildable {
    friend FramePaint;
    friend FrameBufferObject;

private:
    unsigned int _handle;
    virtual GLuint _asColorAttachment(unsigned int GLuint) = 0;

protected:
    void _setHandle(unsigned int handle) {
        _handle = handle;
    }

    unsigned int& _getHandle() {
        return _handle;
    }

public:
    virtual void resize(unsigned int, unsigned int) = 0;
};

#endif //CPPGL_GLTEXTURE_HPP
