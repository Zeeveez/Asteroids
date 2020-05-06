#include "Ship.h"
#include <glm/glm.hpp>
#include <cmath>

namespace Asteroids {
    Ship::Ship(float x, float y, float angle, float dx, float dy, float dAngle, ParticleSystem* particleSystem)
        : particleSystem(particleSystem), PolyShape(x, y, angle, dx, dy, dAngle, 10, std::vector<std::pair<float, float>>()) {
        points.push_back(std::pair<float, float>(0.0f, -1.0f));
        points.push_back(std::pair<float, float>(1.0f, 1.0f));
        points.push_back(std::pair<float, float>(0.0f, 0.0f));
        points.push_back(std::pair<float, float>(-1.0f, 1.0f));
    }

    void Ship::Shield(int duration) {
        shield = duration;
        fullShield = duration;
    }

    int Ship::Shield() {
        return shield;
    }

    void Ship::Explode() {
        alive = false;
    }

    void Ship::Accelerate(float power) {
        dx += power * std::sin(angle);
        dy -= power * std::cos(angle);
        particleSystem->Thrust(x, y, dx, dy, angle);
    }

    void Ship::Update(float maxX, float maxY, bool wrap) {
        if (shield) { shield--; }
        PolyShape::Update(maxX, maxY, wrap);
    }

    void Ship::Draw(Shader& shader, float width, float height) {
        std::vector<glm::vec2> drawPoints = {};
        for (auto& point : points) {
            float pointX = point.first * std::cos(angle) - point.second * std::sin(angle);
            float pointY = point.first * std::sin(angle) + point.second * std::cos(angle);
            drawPoints.push_back(glm::vec2((x + pointX * size) / (width / 2) - 1.0f, (y + pointY * size) / (height / 2) - 1.0f));
        }

        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(drawPoints.size() * sizeof(glm::vec2)), &drawPoints[0], GL_STATIC_DRAW);

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

        shader.Bind();
        glUniform3f(glGetUniformLocation(shader.program, "col"), 1 - (shield ? (float)shield / fullShield : 0), 1.0f, 1.0f);
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)drawPoints.size());
        glDisableVertexAttribArray(0);

        glDeleteBuffers(1, &vertexbuffer);
    }

    Bullet Ship::Fire(float power) {
        return Bullet(x, y, dx + power * std::sin(angle), dy + power * -std::cos(angle));
    }
}