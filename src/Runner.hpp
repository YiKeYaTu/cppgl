
//
// Created by lc on 2022/4/27.
//

#ifndef CPPGL_RUNNER_HPP
#define CPPGL_RUNNER_HPP

#include <Engine.hpp>

class Runner {
private:
    Engine& _engine;
public:
    Runner(Engine& engine): _engine(engine) {
        _engine.initialize();
    }

    void tick() {
        while (!_engine.shouldClose()) {
            _engine.update();
            _engine.swapBuffers();
            _engine.pollEvents();
        }
    }
};

#endif //CPPGL_RUNNER_HPP
