//
// Created by lc on 2022/5/27.
//

#ifndef CPPGL_CAMERA_HPP
#define CPPGL_CAMERA_HPP

#include <math/Vec.hpp>
#include <math/Mat.hpp>
#include <util/coordinate.hpp>

class Camera {
private:
    Vec3f _eye;
    Vec3f _target;
    Vec3f _upDir;
public:
    Camera(const Vec3f& eye, const Vec3f& target, const Vec3f& upDir)
        : _eye(eye), _target(target), _upDir(upDir) {}

    void moveTargetAroundSphere(float x, float y) {
        Vec3f toTarget = _target - _eye;
        auto [ u, v ] = coordinate::toLatLong(toTarget);
        u += x;
        v += y;
        v = std::clamp(v, 0.001f, static_cast<float>(M_PI - 0.001f));
        _target = coordinate::fromLatLong(u, v) + _eye;
    }

    void moveForward(float delta) {
        Vec3f front = normalize((_target - _eye));
        _eye = _eye + front * delta;
    }

    void moveRight(float delta) {
        Vec3f front = normalize(_target - _eye);
        Vec3f right = normalize(_upDir.crossProduct(front));
        _eye = _eye + right * delta;
        _target = _target + right * delta;
    }

    Mat4f asViewMatrix() {
        return Mat4f::LookAt(_eye, _target, _upDir);
    }
};

#endif //CPPGL_CAMERA_HPP
