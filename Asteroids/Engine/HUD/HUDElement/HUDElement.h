#ifndef HUDELEMENT_H
#define HUDELEMENT_H

#include "Engine/Shader/Shader.h"

namespace Engine {
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
    enum class PositionMode {
        PIXELS,
        OPENGL
    };

    class HudElement {
    protected:
        float x;
        float y;
        float width;
        float height;
        Anchor anchor;
        PositionMode positionMode;

    public:
        HudElement(float x, float y, float width, float height, Anchor anchor, PositionMode positionMode);
        virtual void Draw(Shader& shader) = 0;
    };
}

#endif