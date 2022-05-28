//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_LAYOUT_HPP
#define CPPGL_LAYOUT_HPP

#include <vector>
#include <type_traits>
#include <core/xxable/Printable.hpp>
#include <core/xxable/Buildable.hpp>

namespace types {
    template<typename T>
    struct Type2GLenum {};

    template<>
    struct Type2GLenum<float> {
        static const GLenum value = GL_FLOAT;
    };

    template<>
    struct Type2GLenum<unsigned int> {
        static const GLenum value = GL_UNSIGNED_INT;
    };
}

using namespace types;

struct LayoutItem: public Printable {
    GLuint location;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    GLsizei offset;

    LayoutItem(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset)
        : location(location), size(size), type(type), normalized(normalized), stride(stride), offset(offset) {}

    std::string asString() const override {
        std::string output;
        output += "location: " + std::to_string(location) + ", ";
        output += "size: " + std::to_string(size) + ", ";

        switch (type) {
            case GL_FLOAT:
                output += "type: GL_FLOAT, ";
                break;
            case GL_UNSIGNED_INT:
                output += "type: GL_UNSIGNED_INT, ";
                break;
            default:
                output += "type:" + std::to_string(type) + ", ";
                break;
        }

        output += "normalized: " + std::to_string(normalized) + ", ";
        output += "stride: " + std::to_string(stride) + ", ";
        output += "offset: " + std::to_string(offset);

        return output;
    }
};

class RenderUnit;

class Layout: public Printable, public Buildable {
    friend RenderUnit;
private:
    std::vector<LayoutItem> _layoutItems;
    GLsizei _stride = 0;
    GLsizei _numItems = 0;

    void _build() override {
        for (auto& layoutItem : _layoutItems) {
            layoutItem.stride = _stride;
        }
    }
public:
    Layout(std::size_t n = 0) {
        _layoutItems.reserve(n);
    }

    template<typename T>
    void add(GLsizei size, bool normalized = false) {
        assert(_built == false);
        GLsizei offset = _stride;
        GLenum gt = Type2GLenum<T>::value;
        _layoutItems.emplace_back(_layoutItems.size(), size, gt, normalized, -1, offset);
        _stride += size * sizeof(T);
        _numItems += size;
    }

    unsigned int getNumItems() const {
        return _numItems;
    }

    std::string asString() const override {
        std::string output;

        for (auto& layoutItem : _layoutItems) {
            output += layoutItem.asString() + "\n";
        }

        return output;
    }
};

#endif //CPPGL_LAYOUT_HPP
