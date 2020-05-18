#include "Upgrade.h"
#include <cmath>
#include <glm/glm.hpp>

namespace Asteroids {
    Upgrade::Upgrade(float x, float y, float angle, float dx, float dy, float dAngle, float size)
        : Engine::PolyShape(x, y, angle, dx, dy, dAngle, size, std::vector<std::pair<float, float>>()) {
        static const int POINT_COUNT = 30;
        static const float RANDOMNESS = 0.3f;
        static const float PI = 3.1415926535f;
        for (int i = 0; i < POINT_COUNT; i++) {
            float scale = 1 - ((float)rand()) / RAND_MAX * RANDOMNESS;
            points.push_back(std::pair<float, float>(
                std::sin(i * 2 * PI / POINT_COUNT) * scale,
                std::cos(i * 2 * PI / POINT_COUNT) * scale));
        }
    }
}