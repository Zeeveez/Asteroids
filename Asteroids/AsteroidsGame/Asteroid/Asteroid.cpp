#include "Asteroid.h"
#include <cmath>
#include <glm/glm.hpp>

namespace Asteroids {
    Asteroid::Asteroid(float x, float y, float angle, float dx, float dy, float dAngle, float size, Engine::ParticleSystem* particleSystem)
        : particleSystem(particleSystem), Engine::PolyShape(x, y, angle, dx, dy, dAngle, size, std::vector<std::pair<float, float>>()) {
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

    std::vector<Asteroid> Asteroid::Explode() {
        static const float SIZE_REDUCTION = 0.5f;
        static const float MINIMUM_SIZE = 20;
        std::vector<Asteroid> asteroids = {};
        float newSize = size * SIZE_REDUCTION;
        if (newSize > MINIMUM_SIZE) {
            for (int i = 0; i < 4; i++) {
                asteroids.push_back(Asteroid(
                    x,
                    y,
                    ((float)rand()) / RAND_MAX * 360,
                    2 * (0.5f - ((float)rand()) / RAND_MAX),
                    2 * (0.5f - ((float)rand()) / RAND_MAX),
                    0.1f * (0.5f - ((float)rand()) / RAND_MAX),
                    newSize,
                    particleSystem));
            }
        }
        particleSystem->Explosion(x, y);
        return asteroids;
    }
}