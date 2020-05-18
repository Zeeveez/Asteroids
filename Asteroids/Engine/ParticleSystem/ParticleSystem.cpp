#include "ParticleSystem.h"

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
                } else if (age < 180) {
                    return glm::vec3(0.96, 0.65, 0.72);
                } else if (age < 270) {
                    return glm::vec3(1.0f, 1.0f, 1.0f);
                } else if (age < 360) {
                    return glm::vec3(0.96, 0.65, 0.72);
                } else {
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
                } else if (age < 180) {
                    return glm::vec3(0.96, 0.65, 0.72);
                } else if (age < 270) {
                    return glm::vec3(1.0f, 1.0f, 1.0f);
                } else if (age < 360) {
                    return glm::vec3(0.96, 0.65, 0.72);
                } else {
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
                } else if ((float)age / maxAge < 0.6) {
                    return glm::vec3(
                        1.0f,
                        1.0f - ((float)age / maxAge - 0.3f) / 0.3f,
                        0.0f);
                } else {
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
                } else if ((float)age / maxAge < 0.6) {
                    return glm::vec3(
                        1.0f,
                        1.0f - ((float)age / maxAge - 0.3f) / 0.3f,
                        0.0f);
                } else {
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
                    } else if (age / maxAge < 0.6) {
                        return glm::vec3(
                            1.0f,
                            1.0f - ((float)age / maxAge - 0.3f) / 0.3f,
                            0.0f);
                    } else {
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
        //TODO: Update to not use full screen quad to render particles
        GLfloat g_vertex_buffer_data[] = {
             -1.0f, -1.0f,
             1.0f, -1.0f,
              -1.0f,  1.0f,
             1.0f,  1.0f
        };

        // This will identify our vertex buffer
        shader.Bind();
        GLuint vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        for (auto& particle : particles) {
            if (particle.IsAlive()) {
                particle.Draw(shader, width, height);
            }
        }
        glDisableVertexAttribArray(0);


        glDeleteBuffers(1, &vertexbuffer);
    }
}