//
// Created by lc on 2022/5/26.
//

#ifndef CPPGL_StructuredRenderUnit_HPP
#define CPPGL_StructuredRenderUnit_HPP

#include "RenderUnit.hpp"
#include <core/xxable/Usable.hpp>

class StructuredRenderUnit: public Buildable {
public:
    std::vector<std::shared_ptr<StructuredRenderUnit>> _children;
    std::vector<std::shared_ptr<RenderUnit>> _renderUnits;

    void _traverse(StructuredRenderUnit* structuredRenderUnit, std::function<void (RenderUnit*)> callback) {
        if (!structuredRenderUnit) {
            return;
        }

        for (std::shared_ptr<RenderUnit> renderUnit: structuredRenderUnit->_renderUnits) {
            callback(renderUnit.get());
        }

        for (const auto& child : structuredRenderUnit->_children) {
            _traverse(child.get(), callback);
        }
    }

    void _build() override {
        _traverse(this, [](RenderUnit* renderUnit) {
            renderUnit->build();
        });
    }
public:
    StructuredRenderUnit(
        const std::vector<std::shared_ptr<RenderUnit>>& renderUnits,
        const std::vector<std::shared_ptr<StructuredRenderUnit>>& children
    ): _children(children), _renderUnits(renderUnits) {}

    void draw(std::function<void (RenderUnit* renderUnit)> callback) {
        _traverse(this, [&callback](RenderUnit* renderUnit) {
            callback(renderUnit);
        });
    }

};

#endif //CPPGL_StructuredRenderUnit_HPP
