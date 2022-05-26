//
// Created by lc on 2022/5/26.
//

#ifndef CPPGL_StructuredRenderUnit_HPP
#define CPPGL_StructuredRenderUnit_HPP

#include "RenderUnit.hpp"
#include <core/xxable/Usable.hpp>

class StructuredRenderUnit: public Buildable {
private:
    std::vector<std::shared_ptr<StructuredRenderUnit>> _children;
    std::shared_ptr<RenderUnit> _renderUnit;

    void _traverse(StructuredRenderUnit* structuredRenderUnit, std::function<void (std::shared_ptr<RenderUnit>)> callback) {
        if (!structuredRenderUnit) {
            return;
        }

        callback(_renderUnit);

        for (const auto& child : structuredRenderUnit->_children) {
            _traverse(child.get(), callback);
        }
    }

    void _build() override {
        _traverse(this, [](std::shared_ptr<RenderUnit> renderUnit) {
            renderUnit->build();
        });
    }
public:
    void draw(std::function<void (std::shared_ptr<RenderUnit> renderUnit)> callback) {
        _traverse(this, [&callback](std::shared_ptr<RenderUnit> renderUnit) {
            callback(renderUnit);
        });
    }
};

#endif //CPPGL_StructuredRenderUnit_HPP
