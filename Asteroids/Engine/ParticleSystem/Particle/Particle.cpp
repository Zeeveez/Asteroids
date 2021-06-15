#include "Particle.h"

namespace Engine {
    Particle::Particle(float x, float y, float dx, float dy, int age, int maxAge, float size, ParticleFunc colorFunc)
        : x(x), y(y), dx(dx), dy(dy), age(age), maxAge(maxAge), size(size), colorFunc(colorFunc), alive(true) {}

    bool Particle::IsAlive() {
        return alive;
    }

    void Particle::Update(float maxX, float maxY, bool /*wrap*/) {
        x += dx;
        y += dy;
        age++;
        if (x < 0 || x > maxX || y < 0 || y > maxY || age > maxAge) {
            alive = false;
        }
    }

    glm::vec3 Particle::GetParticlePos()
    {
        return { x, y, size };
    }

    glm::vec3 Particle::GetParticleColor()
    {
        return colorFunc(age, maxAge);
    }
}