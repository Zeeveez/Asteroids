#include "ParticleSystem.h"
#include "Engine/Options/Options.h"

namespace Engine {
    void ParticleSystem::CustomExplosion(
        float x, float y, int pointCount, int size,
        int ringCount, float ringGap,
        float speedRandomness, float angleRandomness,
        std::function<float(float, float, float, float)> speedFunc,
        std::function<float(float, float, float, float)> angleFunc,
        std::function<float(float, float, float, float)> startAgeFunc,
        std::function<float(float, float, float, float)> maxAgeFunc,
        std::function<glm::vec3(float)> colorFunc) {
        for (int r = 0; r < ringCount; r++) {
            for (int p = 0; p < pointCount; p++) {
                float speedScale = speedFunc(p, pointCount, r, ringCount);
                speedScale *= 1 + speedRandomness / 2 - speedRandomness * (((float)rand()) / RAND_MAX);
                float angle = angleFunc(p, pointCount, r, ringCount);
                angle *= 1 + angleRandomness / 2 - angleRandomness * (((float)rand()) / RAND_MAX);
                size_t nextPart = NextParticle();
                particles[nextPart].pos.x = x + std::sin(angle) * r * ringGap;
                particles[nextPart].pos.y = y + std::cos(angle) * r * ringGap;
                particles[nextPart].speed.x = std::sin(angle) * speedScale;
                particles[nextPart].speed.y = std::cos(angle) * speedScale;
                particles[nextPart].size = size;
                particles[nextPart].life = maxAgeFunc(p, pointCount, r, ringCount) - startAgeFunc(p, pointCount, r, ringCount);
                particles[nextPart].maxLife = particles[nextPart].life;
                particles[nextPart].colorFunc = colorFunc;
            }
        }
    }

    void ParticleSystem::Explosion(float x, float y) {
        static const float PI = 3.1415926535f;
        CustomExplosion(
            x, y, 100, 5,
            5, 4.0f,
            0.3f, 0.2f,
            [](float point, float pointCount, float ring, float ringCount) { return 1; },
            [](float point, float pointCount, float ring, float ringCount) { return 2 * PI * point / pointCount; },
            [](float point, float pointCount, float ring, float ringCount) { return 0; },
            [](float point, float pointCount, float ring, float ringCount) { return (ringCount - ring) * 30; },
            [](float age) {
                if (age < 0.3) {
                    return glm::vec3(
                        1.0f,
                        1.0f,
                        1.0f - age / 0.3f);
                }
                else if (age < 0.6) {
                    return glm::vec3(
                        1.0f,
                        1.0f - (age - 0.3f) / 0.3f,
                        0.0f);
                }
                else {
                    return glm::vec3(
                        1.0f - (age - 0.6f) / 0.4f,
                        0.0f,
                        0.0f);
                }
            });
    }

    void ParticleSystem::Thrust(float x, float y, float dx, float dy, float angle) {
        static const float RANDOMNESS = 0.5f;
        for (int i = 0; i < 4; i++) {
            float finalAngle = angle + RANDOMNESS / 2 - RANDOMNESS * (((float)rand()) / RAND_MAX);
            size_t nextPart = NextParticle();
            particles[nextPart].pos.x = x;
            particles[nextPart].pos.y = y;
            particles[nextPart].speed.x = -std::sin(finalAngle) + dx;
            particles[nextPart].speed.y = std::cos(finalAngle) + dy;
            particles[nextPart].size = 5.0f;
            particles[nextPart].life = 30.0f;
            particles[nextPart].maxLife = 30.0f;
            particles[nextPart].colorFunc = [](float age) {
                if (age < 0.3f) {
                    return glm::vec3(
                        1.0f,
                        1.0f,
                        1.0f - (age / 0.3f));
                }
                else if (age < 0.6f) {
                    return glm::vec3(
                        1.0f,
                        1.0f - (age - 0.3f) / 0.3f,
                        0.0f);
                }
                else {
                    return glm::vec3(
                        1.0f - (age - 0.6f) / 0.4f,
                        0.0f,
                        0.0f);
                }
            };
        }
    }

    size_t ParticleSystem::NextParticle() {
        lastParticle++;
        lastParticle = lastParticle < PARTICLE_COUNT ? lastParticle : 0;
        return lastParticle;
    }

    void ParticleSystem::Update(float width, float height) {
        size_t i = 0;
        for (auto& particle : particles) {
            if (particle.life > 0.0f) {
                particle.pos += particle.speed;
                particle_render_buffer[i] = particle.pos.x / width * 2 - 1;
                particle_render_buffer[i + 1] = particle.pos.y / height * 2 - 1;
                particle_render_buffer[i + 2] = particle.size;
                auto color = particle.colorFunc(1.0f - particle.life / particle.maxLife);
                particle_render_buffer[i + 3] = color.r;
                particle_render_buffer[i + 4] = color.g;
                particle_render_buffer[i + 5] = color.b;
                particle.life -= 1.0f;
            }
            else {
                particle_render_buffer[i] = -100;   // move dead particles off screen
            }
            i += 6;
        }
    }

    void ParticleSystem::Render() {
        if (Options::drawParticles) {
            shader.Bind();
            glBindVertexArray(VAO);
            glNamedBufferSubData(VBO, NULL, particle_render_buffer.size() * sizeof(GLfloat), particle_render_buffer.data());
            glEnable(GL_PROGRAM_POINT_SIZE);
            glDrawArrays(GL_POINTS, 0, particles.size());
            glDisable(GL_PROGRAM_POINT_SIZE);
            glBindVertexArray(0);
        }
    }
}