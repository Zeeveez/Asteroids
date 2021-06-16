#include "HUDElement.h"

namespace Engine {
    HudElement::HudElement(float x, float y, float width, float height, Anchor anchor, PositionMode positionMode) : x(x), y(y), width(width), height(height), anchor(anchor), positionMode(positionMode) {}
}