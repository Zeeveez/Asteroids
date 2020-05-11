#include "PolyShape.h"
#include <glm/glm.hpp>
#include <cmath>

namespace Engine {
    PolyShape::PolyShape(float x, float y, float angle, float dx, float dy, float dAngle, float size, std::vector<std::pair<float, float>> points)
        : GameObject(x, y, dx, dy, true), angle(angle), dAngle(dAngle), size(size), points(points) {}

    void PolyShape::Draw(Shader& shader, float width, float height) {
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
        glUniform3f(glGetUniformLocation(shader.program, "col"), 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)drawPoints.size());
        glDisableVertexAttribArray(0);

        glDeleteBuffers(1, &vertexbuffer);
    }

    void PolyShape::Update(float maxX, float maxY, bool wrap) {
        x += dx;
        y += dy;
        angle += dAngle;

        if (wrap) {
            if (x > maxX + size) { x -= maxX + size * 2; }
            if (x < -size) { x += maxX + size; }
            if (y > maxY + size) { y -= maxY + size * 2; }
            if (y < -size) { y += maxY + size * 2; }
        }
    }

    Rectangle PolyShape::GetBounds() {
        static const float BOUNDS_SCALE = 0.8f;
        return Rectangle(x - (size * BOUNDS_SCALE), y - (size * BOUNDS_SCALE), size * BOUNDS_SCALE * 2, size * BOUNDS_SCALE * 2);
    }

    void PolyShape::Turn(float delta) {
        angle += delta;
    }
}