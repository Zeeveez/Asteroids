#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "Engine/Shader/Shader.h"

namespace Engine {
    class ProgressBar {
    public:
        enum class Anchor {
            TOP_LEFT,
            TOP_CENTER,
            TOP_RIGHT,
            MIDDLE_LEFT,
            MIDDLE_CENTER,
            MIDDLE_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_CENTER,
            BOTTOM_RIGHT
        };

    private:
        float* val;
        float* min;
        float* max;

    public:
        ProgressBar(float* val, float* min, float* max);
        void Draw(Shader& shader, float x, float y, float width, float height, Anchor anchor);
    };
}


#endif