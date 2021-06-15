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

    void Particle::Draw(Shader& shader, float width, float height) {
        GLfloat g_vertex_buffer_data[] = {
             x / (width / 2) - 1.0f, y / (height / 2) - 1.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glUniform1f(glGetUniformLocation(shader.program, "size"), size);
        glUniform3fv(glGetUniformLocation(shader.program, "col"), 1, &colorFunc(age, maxAge)[0]);
        glDrawArrays(GL_POINTS, 0, 1);
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