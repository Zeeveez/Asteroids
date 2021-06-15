#include "ParticleSystem.h"
#include "Engine/Options/Options.h"

namespace Engine {
    void ParticleSystem::CustomExplosion(
        float x, float y, int pointCount, int size,
        int ringCount, float ringGap,
        float speedRandomness, float angleRandomness,
        std::function<float(float, float, float, float)> speedFunc,
        std::function<float(float, float, float, float)> angleFunc,
        std::function<int(float, float, float, float)> startAgeFunc,
        std::function<int(float, float, float, float)> maxAgeFunc,
        std::function<glm::vec3(int, int)> colorFunc) {
        for (int r = 0; r < ringCount; r++) {
            for (int p = 0; p < pointCount; p++) {
                float speedScale = speedFunc(p, pointCount, r, ringCount);
                speedScale *= 1 + speedRandomness / 2 - speedRandomness * (((float)rand()) / RAND_MAX);
                float angle = angleFunc(p, pointCount, r, ringCount);
                angle *= 1 + angleRandomness / 2 - angleRandomness * (((float)rand()) / RAND_MAX);
                particles.push_back(Particle(
                    x + std::sin(angle) * r * ringGap,
                    y + std::cos(angle) * r * ringGap,
                    std::sin(angle) * speedScale,
                    std::cos(angle) * speedScale,
                    startAgeFunc(p, pointCount, r, ringCount),
                    maxAgeFunc(p, pointCount, r, ringCount),
                    size,
                    colorFunc));
            }
        }
    }

    void ParticleSystem::CustomExplosion(float x, float y) {
        static const float PI = 3.1415926535f;
        CustomExplosion(
            x, y, 100, 5,
            5, 6.0f,
            0.3f, 0.3f,
            [](float point, float pointCount, float ring, float ringCount) { return 1; },
            [](float point, float pointCount, float ring, float ringCount) { return 2 * PI * point / pointCount; },
            [](float point, float pointCount, float ring, float ringCount) { return ring * 90; },
            [](float point, float pointCount, float ring, float ringCount) { return (ring + 1) * 90; },
            [](int age, int maxAge) {
                if (age < 90) {
                    return glm::vec3(0.33f, 0.8f, 0.988f);
                }
                else if (age < 180) {
                    return glm::vec3(0.96, 0.65, 0.72);
                }
                else if (age < 270) {
                    return glm::vec3(1.0f, 1.0f, 1.0f);
                }
                else if (age < 360) {
                    return glm::vec3(0.96, 0.65, 0.72);
                }
                else {
                    return glm::vec3(0.33f, 0.8f, 0.988f);
                }
            });
    }

    void ParticleSystem::TransExplosion(float x, float y) {
        static const float PI = 3.1415926535f;
        CustomExplosion(
            x, y, 100, 5,
            5, 6.0f,
            0.3f, 0.3f,
            [](float point, float pointCount, float ring, float ringCount) { return 1; },
            [](float point, float pointCount, float ring, float ringCount) { return 2 * PI * point / pointCount; },
            [](float point, float pointCount, float ring, float ringCount) { return ring * 90; },
            [](float point, float pointCount, float ring, float ringCount) { return (ring + 1) * 90; },
            [](int age, int maxAge) {
                if (age < 90) {
                    return glm::vec3(0.33f, 0.8f, 0.988f);
                }
                else if (age < 180) {
                    return glm::vec3(0.96, 0.65, 0.72);
                }
                else if (age < 270) {
                    return glm::vec3(1.0f, 1.0f, 1.0f);
                }
                else if (age < 360) {
                    return glm::vec3(0.96, 0.65, 0.72);
                }
                else {
                    return glm::vec3(0.33f, 0.8f, 0.988f);
                }
            });
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
            [](int age, int maxAge) {
                if ((float)age / maxAge < 0.3) {
                    return glm::vec3(
                        1.0f,
                        1.0f,
                        1.0f - (float)age / maxAge / 0.3f);
                }
                else if ((float)age / maxAge < 0.6) {
                    return glm::vec3(
                        1.0f,
                        1.0f - ((float)age / maxAge - 0.3f) / 0.3f,
                        0.0f);
                }
                else {
                    return glm::vec3(
                        1.0f - ((float)age / maxAge - 0.6f) / 0.4f,
                        0.0f,
                        0.0f);
                }
            });
    }

    void ParticleSystem::SpiralBurst(float x, float y) {
        static const float PI = 3.1415926535f;
        CustomExplosion(
            x, y, 100, 5,
            5, 0.0f,
            0.0f, 0.0f,
            [](float point, float pointCount, float ring, float ringCount) { return 5 * (float)point / pointCount; },
            [](float point, float pointCount, float ring, float ringCount) { return point * 2 * PI / pointCount + 2 * PI * ((float)ring) / ringCount; },
            [](float point, float pointCount, float ring, float ringCount) { return 0; },
            [](float point, float pointCount, float ring, float ringCount) { return 60; },
            [](int age, int maxAge) {
                if ((float)age / maxAge < 0.3) {
                    return glm::vec3(
                        1.0f,
                        1.0f,
                        1.0f - (float)age / maxAge / 0.3f);
                }
                else if ((float)age / maxAge < 0.6) {
                    return glm::vec3(
                        1.0f,
                        1.0f - ((float)age / maxAge - 0.3f) / 0.3f,
                        0.0f);
                }
                else {
                    return glm::vec3(
                        1.0f - ((float)age / maxAge - 0.6f) / 0.4f,
                        0.0f,
                        0.0f);
                }
            });
    }

    void ParticleSystem::HeartBurst(float x, float y) {
        static const float PI = 3.1415926535f;
        CustomExplosion(
            x, y, 100, 3,
            1, 0.0f,
            0.0f, 0.0f,
            [](float point, float pointCount, float ring, float ringCount) { float speedScale = (float)(point < pointCount / 2.0f ? point : pointCount - point) / (pointCount / 2); speedScale /= (speedScale + 1); speedScale *= 3; return speedScale + 0.1; },
            [](float point, float pointCount, float ring, float ringCount) { return 2 * PI * point / pointCount; },
            [](float point, float pointCount, float ring, float ringCount) { return 0; },
            [](float point, float pointCount, float ring, float ringCount) { return 60; },
            [](double age, double maxAge) {
                return glm::vec3(
                    1.0f,
                    0.0f,
                    1.0f
                );
            });
    }

    void ParticleSystem::Thrust(float x, float y, float dx, float dy, float angle) {
        static const float RANDOMNESS = 0.5f;
        for (int i = 0; i < 4; i++) {
            float finalAngle = angle + RANDOMNESS / 2 - RANDOMNESS * (((float)rand()) / RAND_MAX);
            particles.push_back(Particle(
                x,
                y,
                -std::sin(finalAngle) + dx,
                std::cos(finalAngle) + dy,
                0,
                40,
                5,
                [](double age, double maxAge) {
                    if (age / maxAge < 0.3) {
                        return glm::vec3(
                            1.0f,
                            1.0f,
                            1.0f - (float)age / maxAge / 0.3f);
                    }
                    else if (age / maxAge < 0.6) {
                        return glm::vec3(
                            1.0f,
                            1.0f - ((float)age / maxAge - 0.3f) / 0.3f,
                            0.0f);
                    }
                    else {
                        return glm::vec3(
                            1.0f - ((float)age / maxAge - 0.6f) / 0.4f,
                            0.0f,
                            0.0f);
                    }
                }));
        }
    }

    void ParticleSystem::Update(float width, float height) {
        for (auto& particle : particles) {
            particle.Update(width, height);
        }
        particles.erase(std::remove_if(
            particles.begin(), particles.end(),
            [](Particle& particle) {
                return !particle.IsAlive();
            }), particles.end());
    }

    void ParticleSystem::Render(float width, float height) {
        if (Options::drawParticles) {
            shader.Bind();

            GLfloat* bufferdata = new GLfloat[particles.size() * 6];    // x,y,size,r,g,b
            int i = 0;
            for (auto& p : particles) {
                auto pos = p.GetParticlePos();
                auto col = p.GetParticleColor();
                bufferdata[i] = pos.x / width * 2 - 1;
                bufferdata[i + 1] = pos.y / height * 2 - 1;
                bufferdata[i + 2] = pos.z;
                bufferdata[i + 3] = col.r;
                bufferdata[i + 4] = col.g;
                bufferdata[i + 5] = col.b;
                i += 6;
            }

            GLuint VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, particles.size() * 6 * sizeof(GLfloat), bufferdata, GL_DYNAMIC_DRAW);
            //glVertexAttribDivisor(0, 1);
            //glVertexAttribDivisor(1, 1);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);   // x,y,size
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));   // r,g,b

            glEnable(GL_PROGRAM_POINT_SIZE);
            //glDrawArraysInstanced(GL_POINTS, 0, 1, particles.size());
            glDrawArrays(GL_POINTS, 0, particles.size());
            glDisable(GL_PROGRAM_POINT_SIZE);

            //glVertexAttribDivisor(0, 0);
            //glVertexAttribDivisor(1, 0);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDeleteBuffers(1, &vertexbuffer);
            delete[] bufferdata;

            glBindVertexArray(0);
            glDeleteVertexArrays(1, &VAO);
        }
    }
}