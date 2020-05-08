#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle/Particle.h"
#include "Shader/Shader.h"
#include <vector>
#include <functional>

namespace Asteroids {
    class ParticleSystem {
    private:
        std::vector<Particle> particles = {};
        Shader shader = Shader("particle");

    public:
        void CustomExplosion(
            float x, float y, int pointCount, int size,
            int ringCount, float ringGap,
            float speedRandomness, float angleRandomness,
            std::function<float(float, float, float, float)> speedFunc,
            std::function<float(float, float, float, float)> angleFunc,
            std::function<int(float, float, float, float)> startAgeFunc,
            std::function<int(float, float, float, float)> maxAgeFunc,
            std::function<glm::vec3(int, int)> colorFunc);
        void CustomExplosion(float x, float y);
        void TransExplosion(float x, float y);
        void Explosion(float x, float y);
        void SpiralBurst(float x, float y);
        void HeartBurst(float x, float y);
        void Thrust(float x, float y, float dx, float dy, float angle);
        void Update(float width, float height);
        void Render(float width, float height);
    };
}

#endif