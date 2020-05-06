#include "Rectangle.h"

namespace Asteroids {
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
}