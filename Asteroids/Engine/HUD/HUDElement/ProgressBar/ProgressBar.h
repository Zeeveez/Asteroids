#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "Engine/HUD/HUDElement/HUDElement.h"

namespace Engine {
    class ProgressBar : HudElement {
    private:
        float* val;
        float* min;
        float* max;

    public:
        ProgressBar(float x, float y, float width, float height, Anchor anchor, PositionMode positionMode, float* val, float* min, float* max);
        void Draw(Shader& shader) override;
    };
}


#endif