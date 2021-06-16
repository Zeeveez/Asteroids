#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <glm/glm.hpp>
#include "Engine/Shader/Shader.h"
#include <array>
#include <functional>

namespace Engine {
    class ParticleSystem {
    private:
        struct Particle {
            glm::vec2 pos;
            glm::vec2 speed;
            std::function<glm::vec3(float)> colorFunc;
            float size;
            float life;
            float maxLife;
        };
        static const size_t PARTICLE_COUNT = 10000;
        static inline std::array<Particle, PARTICLE_COUNT> particles = {};
        static inline std::array<GLfloat, PARTICLE_COUNT * 6> particle_render_buffer = {};
        Shader shader = Shader("particle");
        GLuint VAO;
        GLuint VBO;

    public:
        static inline size_t lastParticle = 0;
        size_t NextParticle();
        void Update(float width, float height);
        void Render();

        ParticleSystem() {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, particle_render_buffer.size() * sizeof(GLfloat), particle_render_buffer.data(), GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);   // x,y,size
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));   // r,g,b

            glBindVertexArray(0);
        }

        ~ParticleSystem() {
            glBindVertexArray(VAO);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
            glDeleteBuffers(1, &VBO);
            glBindVertexArray(0);
            glDeleteVertexArrays(1, &VAO);
        }

        void CustomExplosion(
            float x, float y, int pointCount, int size,
            int ringCount, float ringGap,
            float speedRandomness, float angleRandomness,
            std::function<float(float, float, float, float)> speedFunc,
            std::function<float(float, float, float, float)> angleFunc,
            std::function<float(float, float, float, float)> startAgeFunc,
            std::function<float(float, float, float, float)> maxAgeFunc,
            std::function<glm::vec3(float)> colorFunc);
        void Explosion(float x, float y);
        void Thrust(float x, float y, float dx, float dy, float angle);
    };
}

#endif