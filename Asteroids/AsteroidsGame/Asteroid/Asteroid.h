#ifndef ASTEROID_H
#define ASTEROID_H

#include "Engine/Rectangle/GameObject/PolyShape/PolyShape.h"
#include "Engine/ParticleSystem/ParticleSystem.h"
#include <vector>

namespace Asteroids {
    class Asteroid : public Engine::PolyShape {
    private:
        Engine::ParticleSystem* particleSystem;

    public:
        Asteroid(float x, float y, float angle, float dx, float dy, float dAngle, float size, Engine::ParticleSystem* particleSystem);
        std::vector<Asteroid> Explode();
        std::pair<float, float> GetPos();
        std::pair<float, float> GetVel();
        Asteroid(const Asteroid&) = default;
        Asteroid& operator=(const Asteroid&) = default;
    };
}

#endif