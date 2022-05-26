//
// Created by lc on 2022/4/25.
//

#ifndef CPPGL_PRINTABLE_HPP
#define CPPGL_PRINTABLE_HPP

#include <iostream>
#include <string>

class Printable {
public:
    virtual std::string asString() const = 0;
    virtual ~Printable() {}
};

std::ostream& operator<<(std::ostream& os, const Printable& printable) {
    os << printable.asString();
    return os;
}

#endif //CPPGL_PRINTABLE_HPP
