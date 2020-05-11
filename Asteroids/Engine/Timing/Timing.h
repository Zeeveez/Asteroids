#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <GLFW/glfw3.h>

namespace Engine {
    class GameTimer {
    public:
        GameTimer(double framerate);
        void Start();
        void Tick();
        bool ConsumeTick();
        double GetFrameRate();
    private:
        double dt;
        double currentTime;
        double accumulator;
    };
}

#endif