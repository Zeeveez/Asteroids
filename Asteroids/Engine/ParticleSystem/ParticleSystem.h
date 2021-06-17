#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <glm/glm.hpp>
#include "Engine/Shader/Shader.h"
#include "Engine/Options/Options.h"
#include <array>
#include <functional>
#include <thread>

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
        static inline std::array<GLfloat, PARTICLE_COUNT * 6> particleDataBufferData = {};
        Shader shader = Shader("particle");
        GLuint VAO;
        GLuint particleVertexBuffer;
        GLuint particleDataBuffer;

    public:
        static inline size_t lastParticle = 0;
        size_t NextParticle();
        void Update(float width, float height);
        void Render();

        ParticleSystem() {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            static const GLfloat particleVertexBufferData[] = {
                 -0.5f, -0.5f,
                 0.5f, -0.5f,
                 -0.5f, 0.5f,
                 0.5f, 0.5f
            }; 

            shader.Bind();
            glUniform2f(glGetUniformLocation(shader.program, "res"), Engine::Options::screenSize.first, Engine::Options::screenSize.second);

            glGenBuffers(1, &particleVertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, particleVertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(particleVertexBufferData), particleVertexBufferData, GL_STATIC_DRAW);

            // vert pos's
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
            glVertexAttribDivisor(0, 0);

            glGenBuffers(1, &particleDataBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, particleDataBuffer);
            glBufferData(GL_ARRAY_BUFFER, particleDataBufferData.size() * sizeof(GLfloat), particleDataBufferData.data(), GL_DYNAMIC_DRAW);

            // x,y,size
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
            glVertexAttribDivisor(1, 1);

            // r,g,b
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
            glVertexAttribDivisor(2, 1);

            glBindVertexArray(0);
        }

        ~ParticleSystem() {
            glBindVertexArray(VAO);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
            glDeleteBuffers(1, &particleVertexBuffer);
            glDeleteBuffers(1, &particleDataBuffer);
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