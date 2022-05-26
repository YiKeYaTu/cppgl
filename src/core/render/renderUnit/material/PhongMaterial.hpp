//
// Created by lc on 2022/5/25.
//

#ifndef CPPGL_PHONGMATERIAL_HPP
#define CPPGL_PHONGMATERIAL_HPP

#include <math/Vec.hpp>
#include <memory>
#include "Material.hpp"

class PhongMaterial {
private:
    Vec3f _diffuseCoefficient;
    Vec3f _specularCoefficient;
    Vec3f _ambientCoefficient;

    std::shared_ptr<unsigned int[]> _diffuseMap = nullptr;
    std::shared_ptr<unsigned int[]> _specularMap = nullptr;
    std::shared_ptr<unsigned int[]> _ambientMap = nullptr;
public:
    const Vec3f& getDiffuseCoefficient() const {
        return _diffuseCoefficient;
    }
    const Vec3f& getSpecularCoefficient() const {
        return _specularCoefficient;
    }
    const Vec3f& getAmbientCoefficient() const {
        return _ambientCoefficient;
    }
    const std::shared_ptr<unsigned int[]> getDiffuseMap() const {
        return _diffuseMap;
    }
    const std::shared_ptr<unsigned int[]> geSpecularMap() const {
        return _specularMap;
    }
    const std::shared_ptr<unsigned int[]> getAmbientMap() const {
        return _ambientMap;
    }
};

#endif //CPPGL_PHONGMATERIAL_HPP
