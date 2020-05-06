#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace Asteroids {
    class Rectangle {
    private:
        float x;
        float y;
        float width;
        float height;

    public:
        Rectangle(float x, float y, float width, float height);
        bool Intersects(Rectangle otherRect);
    };
}

#endif