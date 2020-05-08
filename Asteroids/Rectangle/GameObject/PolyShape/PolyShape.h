#ifndef POLYSHAPE_H
#define POLYSHAPE_H

#include "Rectangle/GameObject/GameObject.h"
#include <utility>
#include <vector>

namespace Asteroids {
    class PolyShape : public GameObject {
    protected:
        float angle;
        float dAngle;
        float size;
        std::vector<std::pair<float, float>> points;

    public:
        PolyShape() = default;
        PolyShape(float x, float y, float angle, float dx, float dy, float dAngle, float size, std::vector<std::pair<float, float>> points);
        void Draw(Shader& shader, float width, float height) override;
        void Update(float maxX, float maxY, bool wrap = true) override;
        Rectangle GetBounds() override;
        void Turn(float delta);
    };
}

#endif