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
    std::vector<std::shared_ptr<RenderUnit>> _renderUnits;

    void _traverse(StructuredRenderUnit* structuredRenderUnit, std::function<void (std::shared_ptr<RenderUnit>)> callback) {
        if (!structuredRenderUnit) {
            return;
        }

        for (const auto& renderUnit : structuredRenderUnit->_renderUnits) {
            callback(renderUnit);
        }

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
    StructuredRenderUnit(
        const std::vector<std::shared_ptr<RenderUnit>>& renderUnits,
        const std::vector<std::shared_ptr<StructuredRenderUnit>>& children
    ): _children(children), _renderUnits(renderUnits) {}

    void draw(std::function<void (std::shared_ptr<RenderUnit> renderUnit)> callback) {
        _traverse(this, [&callback](std::shared_ptr<RenderUnit> renderUnit) {
            callback(renderUnit);
        });
    }
};

#endif //CPPGL_StructuredRenderUnit_HPP
