//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_BUILDABLE_HPP
#define CPPGL_BUILDABLE_HPP

class Buildable {
private:
    virtual void _build() = 0;
    virtual void _destroy() {}

protected:
    bool _built = false;

public:
    virtual ~Buildable() = default;

    virtual void build() {
        if (!_built) {
            _built = true;
            _build();
        }
    }

    virtual void destroy() {
        if (_built) {
            _built = false;
            _destroy();
        }
    }

    bool isBuilt() const {
        return _built;
    }
};

#endif //CPPGL_BUILDABLE_HPP
