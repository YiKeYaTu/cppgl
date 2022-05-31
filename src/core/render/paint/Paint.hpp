//
// Created by lc on 2022/5/30.
//

#ifndef CPPGL_PAINT_HPP
#define CPPGL_PAINT_HPP

#include "core/xxable/Usable.hpp"
#include "core/xxable/Buildable.hpp"
#include "core/buffer/FrameBufferObject.hpp"
#include "core/gl/glDraw.hpp"
#include "core/gl/configurer/glDepthTestConfigurer.hpp"
#include "macro/debug.hpp"
#include "core/render/renderUnit/RenderUnit.hpp"
#include "core/render/paint/RenderContext.hpp"

class Paint: public Buildable {
private:
    RenderContext _renderContext;

    std::unique_ptr<FrameBufferObject> _framebufferObject;

    Paint(): _framebufferObject(nullptr) {}

    void _build() override {
        if (_framebufferObject) {
            _framebufferObject->build();
        }
    }

public:
    Paint(
        const std::vector<Texture*>& colorTextures
        , const std::vector<RenderBufferObject*>& renderBufferObjects = {}
    ): _framebufferObject(std::make_unique<FrameBufferObject>(colorTextures, renderBufferObjects)) {}

    void use(std::function<void (RenderContext& renderContext)> fn) {
        requireBuilt()
        if (_framebufferObject) {
            _framebufferObject->use();
        } else {
            glFrameBuffer::bind(0);
        }
        fn(_renderContext);
    }

    Texture& getColorTexture(unsigned int idx) {
        return *(_framebufferObject->_colorTextures.at(idx));
    }

    static Paint& getScreenPaint() {
        static Paint paint;
        paint.build();
        return paint;
    }
};

#endif //CPPGL_PAINT_HPP
