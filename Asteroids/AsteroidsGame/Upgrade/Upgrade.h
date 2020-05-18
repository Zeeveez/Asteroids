#ifndef UPGRADE_H
#define UPGRADE_H

#include "Engine/Rectangle/GameObject/PolyShape/PolyShape.h"
#include "Engine/ParticleSystem/ParticleSystem.h"

namespace Asteroids {
    class Upgrade : public Engine::PolyShape {
    public:
        Upgrade(float x, float y, float angle, float dx, float dy, float dAngle, float size);
        Upgrade(const Upgrade&) = default;
        Upgrade& operator=(const Upgrade&) = default;
    };
}

#endif