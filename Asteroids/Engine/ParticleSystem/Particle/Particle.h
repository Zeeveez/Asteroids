#ifndef PARTICLE_H
#define PARTICLE_H

#include "Engine/Shader/Shader.h"
#include <functional>
#include <glm/glm.hpp>

namespace Engine {
    class Particle {
    public:
        typedef std::function<glm::vec3(double, double)> ParticleFunc;

    protected:
        float x;
        float y;
        float dx;
        float dy;
        bool alive;
        int age;
        int maxAge;
        double size;
        ParticleFunc colorFunc;

    public:
        Particle(float x, float y, float dx, float dy, int age, int maxAge, double size, ParticleFunc colorFunc);
        bool IsAlive();
        void Update(float maxX, float maxY, bool wrap = false);
        void Draw(Shader& shader, float width, float height);
    };
}

#endif