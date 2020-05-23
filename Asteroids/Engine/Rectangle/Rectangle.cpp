#include "Rectangle.h"

namespace Engine {
    Rectangle::Rectangle(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}

    bool Rectangle::Intersects(Rectangle otherRect) {
        if (x > otherRect.x + otherRect.width) {
            return false;
        }
        if (y > otherRect.y + otherRect.height) {
            return false;
        }
        if (x + width < otherRect.x) {
            return false;
        }
        if (y + height < otherRect.y) {
            return false;
        }
        return true;
    }

    std::vector<std::pair<float, float>> Rectangle::GetPoints() {
        return {
            { -1.0f, -1.0f },
            { 1.0f, -1.0f },
            { 1.0f, 0.0f },
            { -1.0f, 1.0f }
        };
    }
}