#include "Bullet.h"
#include "GL/glew.h"

namespace Asteroids {
    Bullet::Bullet(float x, float y, float dx, float dy)
        : GameObject(x, y, dx, dy, true) {}

    void Bullet::Update(float maxX, float maxY, bool /*wrap*/) {
        x += dx;
        y += dy;
        if (x < 0 || x > maxX || y < 0 || y > maxY) {
            alive = false;
        }
    }

    void Bullet::Draw(Engine::Shader& shader, float width, float height) {
        GLfloat g_vertex_buffer_data[] = {
             (x - 1) / (width / 2) - 1.0f, (y - 1) / (height / 2) - 1.0f,
             (x + 1) / (width / 2) - 1.0f, (y - 1) / (height / 2) - 1.0f,
             (x - 1) / (width / 2) - 1.0f, (y + 1) / (height / 2) - 1.0f,
             (x + 1) / (width / 2) - 1.0f, (y + 1) / (height / 2) - 1.0f
        };

        // This will identify our vertex buffer
        shader.Bind();
        glUniform3f(glGetUniformLocation(shader.program, "col"), 1.0f, 1.0f, 1.0f);
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
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);


        glDeleteBuffers(1, &vertexbuffer);
    }

    Engine::Rectangle Bullet::GetBounds() {
        return Engine::Rectangle(x - 1, y - 1, 3, 3);
    }
}