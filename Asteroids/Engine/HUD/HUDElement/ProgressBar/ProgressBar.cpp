#include "ProgressBar.h"
#include <GLFW\glfw3.h>

namespace Engine {
    ProgressBar::ProgressBar(float x, float y, float width, float height, Anchor anchor, PositionMode positionMode, float* val, float* min, float* max) : HudElement(x, y, width, height, anchor, positionMode), val(val), min(min), max(max) {}

    void ProgressBar::Draw(Shader& shader) {
        // TODO : Actually use position mode and anchor
        GLfloat g_vertex_buffer_data[] = {
             x, y,
             x + width * (*val - *min) / (*max - *min), y,
             x,  y - height,
             x + width * (*val - *min) / (*max - *min),  y - height
        };

        shader.Bind();
        glUniform3f(glGetUniformLocation(shader.program, "col"), 1.0f, 1.0f, 1.0f);

        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDisableVertexAttribArray(0);

        glDeleteBuffers(1, &vertexbuffer);
    }
}