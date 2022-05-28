//
// Created by lc on 2022/5/28.
//

#ifndef CPPGL_COORDINATE_HPP
#define CPPGL_COORDINATE_HPP

#include <math/Vec.hpp>
#include <cmath>

namespace coordinate {
    std::tuple<float, float> toLatLong(const Vec3f& v) {
        const Vec3f nv = v.normalized();
        float x = nv.x(), y = nv.y(), z = nv.z();
        float theta = atan2(x, z);
        float phi = acos(y);
        return { theta, phi };
    }
    Vec3f fromLatLong(float theta, float phi) {
        float sinPhi = sin(phi);
        float x = sinPhi * sin(theta);
        float z = sinPhi * cos(theta);
        float y = cos(phi);
        return { x, y, z };
    }
}

#endif //CPPGL_COORDINATE_HPP
