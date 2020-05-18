#include "Upgrade.h"
#include <cmath>
#include <glm/glm.hpp>

namespace Asteroids {
    Upgrade::Upgrade(float x, float y, float angle, float dx, float dy, float dAngle, float size)
        : Engine::PolyShape(x, y, angle, dx, dy, dAngle, size, { {0,1},{0.3f,0.3f},{1,0},{0.3f,-0.3f},{0,-1},{-0.3f,-0.3f},{-1,0},{-0.3f,0.3f} }) {}
}