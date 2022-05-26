//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_USEABLE_HPP
#define CPPGL_USEABLE_HPP

class Usable {
public:
    virtual ~Usable() = default;
    virtual void use() = 0;
};

#endif //CPPGL_USEABLE_HPP
