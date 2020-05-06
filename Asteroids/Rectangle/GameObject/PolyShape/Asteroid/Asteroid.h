#ifndef ASTEROID_H
#define ASTEROID_H

#include "../PolyShape.h"
#include "../../../../ParticleSystem/ParticleSystem.h"
#include <vector>

namespace Asteroids {
    class Asteroid : public PolyShape {
    private:
        ParticleSystem* particleSystem;

    public:
        Asteroid(float x, float y, float angle, float dx, float dy, float dAngle, float size, ParticleSystem* particleSystem);
        std::vector<Asteroid> Explode();
        Asteroid(const Asteroid&) = default;
        Asteroid& operator=(const Asteroid&) = default;
    };
}

#endif