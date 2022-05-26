//
// Created by lc on 2022/5/23.
//

#ifndef CPPGL_QUATERNION_HPP
#define CPPGL_QUATERNION_HPP

#include <math/Vec.hpp>
#include <math/Mat.hpp>

class Quaternion {
    friend std::ostream& operator<<(std::ostream &os, const Quaternion& quaternion);
private:
    Vec4f _container;
public:
    Quaternion(float theta, const Vec3f& n) {
        if (n.length() - 1.0 >= 1e-4) {
            throw std::runtime_error("Rotation axis is not normalized");
        }
        float alpha = theta / 2;
        _container[0] = n.x() * sin(alpha);
        _container[1] = n.y() * sin(alpha);
        _container[2] = n.z() * sin(alpha);
        _container[3] = cos(alpha);
    }

    Quaternion(const Quaternion& rhs): _container(rhs._container) {}
    Quaternion(const Vec4f& v): _container(v) {}
    Quaternion(float x, float y, float z, float w): _container{ x, y, z, w } {}

    Quaternion operator*(const Quaternion& rhs) const {
        Vec3f v = _container.xyz(), u = rhs._container.xyz();
        float a = _container.w(), e = rhs._container.w();
        Vec3f xyz = v.crossProduct(u) + u*a + v*e;
        return Quaternion(xyz.x(), xyz.y(), xyz.z(), a*e - v.dot(u));
    }

    Quaternion operator*(float rhs) const {
        return Quaternion(_container * rhs);
    }

    Quaternion operator+(const Quaternion& rhs) const {
        return Quaternion(_container + rhs._container);
    }

    Quaternion log() const {
        float alpha = acos(_container.w());
        Vec3f n = _container.xyz();
        n = n / n.length() * alpha;
        return Quaternion(n.x(), n.y(), n.z(), 0);
    }

    Quaternion exp() const {
        float alpha = _container.xyz().length();
        Vec3f n;

        if (alpha != 0.0) {
            n = _container.xyz() / alpha;
        }

        return Quaternion(n.x() * sin(alpha), n.y() * sin(alpha), n.z() * sin(alpha), cos(alpha));
    }

    Quaternion pow(float e) const {
        return (log() * e).exp();
    }

    Quaternion inverse() const {
        return Quaternion(-_container.x(), -_container.y(), -_container.z(), _container.w());
    }

    Quaternion slerp(const Quaternion& q1, float t) const {
        Quaternion delta = (q1 * inverse()).pow(t);
        return delta * (*this);
    }

    Quaternion slerpFaster(const Quaternion& q1, float t) const {
        float k0, k1;
        Vec4f v0 = _container, v1 = q1._container;
        float cos = _container.dot(q1._container);

        if (cos < 0.0f) {
            v1 = -v1;
            cos = -cos;
        }

        if (cos > 0.99f) {
            k0 = 1.0f - t;
            k1 = t;
        } else {
            float sinW = sqrt(1.0f - cos*cos);
            float oneOverSinW = 1.0f / sinW;
            float w = acos(cos);

            k0 = sin((1.0f - t) * w) * oneOverSinW;
            k1 = sin(t * w) * oneOverSinW;
        }

        return Quaternion(v0 * k0 + v1 * k1);
    }

    Mat4f asRotationMatrix() const {
        Mat4f identity = Mat4f::Identity();
        float a = _container.w(), b = _container.x(), c = _container.y(), d = _container.z();
        identity[0][0] = 1 - 2*c*c - 2*d*d;
        identity[0][1] = 2*b*c + 2*a*d;
        identity[0][2] = 2*b*d - 2*a*c;

        identity[1][0] = 2*b*c - 2*a*d;
        identity[1][1] = 1 - 2*b*b - 2*d*d;
        identity[1][2] = 2*a*b + 2*c*d;

        identity[2][0] = 2*a*c + 2*b*d;
        identity[2][1] = 2*c*d - 2*a*b;
        identity[2][2] = 1 - 2*b*b - 2*c*c;
        return identity;
    }

};

std::ostream& operator<<(std::ostream &os, const Quaternion& quaternion) {
    return os << quaternion._container;
}

#endif //CPPGL_QUATERNION_HPP
