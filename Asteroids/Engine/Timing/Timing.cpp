#include "Timing.h"

#include <GLFW/glfw3.h>

namespace Engine {
    GameTimer::GameTimer(double framerate) {
        dt = framerate;
        Start();
    }

    void GameTimer::Start() {
        currentTime = glfwGetTime();
        accumulator = 0.0;
    }

    void GameTimer::Tick() {
        double newTime = glfwGetTime();
        accumulator += newTime - currentTime;
        currentTime = newTime;
    }

    bool GameTimer::ConsumeTick() {
        if (accumulator >= dt) {
            accumulator -= dt;
            return true;
        }
        return false;
    }

    double GameTimer::GetFrameRate() {
        return dt;
    }
}