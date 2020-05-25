#include "Particle.h"

namespace Engine {
    Particle::Particle(float x, float y, float dx, float dy, int age, int maxAge, double size, ParticleFunc colorFunc)
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
             (x - size / 2) / (width / 2) - 1.0f, (y - size / 2) / (height / 2) - 1.0f,
             (x + size / 2) / (width / 2) - 1.0f, (y - size / 2) / (height / 2) - 1.0f,
             (x - size / 2) / (width / 2) - 1.0f, (y + size / 2) / (height / 2) - 1.0f,
             (x + size / 2) / (width / 2) - 1.0f, (y + size / 2) / (height / 2) - 1.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glUniform1f(glGetUniformLocation(shader.program, "size"), size);
        glUniform2f(glGetUniformLocation(shader.program, "pos"), x, y);
        glUniform3fv(glGetUniformLocation(shader.program, "col"), 1, &colorFunc(age, maxAge)[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}