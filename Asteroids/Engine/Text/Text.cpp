#include "Text.h"

namespace Engine {
    void DrawString(Texture& texture, Shader& shader, float x, float y, int size, std::string str) {
        int i = 0;
        int w;
        int h;
        glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
        float charHeight = size * 2.0f / h;
        float charWidth = size * 1.0f / w;
        for (const auto& c : str) {
            DrawCharacter(texture, shader, x + charWidth * i++, y, charWidth, charHeight, c);
        }
    }

    void DrawCharacter(Texture& texture, Shader& shader, float x, float y, float w, float h, char c) {
        GLfloat g_vertex_buffer_data[] = {
             x, y,
             x + w, y,
             x,  y + h,
             x + w,  y + h
        };
        float charWidth = 1.0f / 16;
        float charHeight = 1.0f / 8;
        int charX = c % 16;
        int charY = c / 16;
        GLfloat uv_buffer_data[] = {
             charX * charWidth, (7 - charY) * charHeight,
             (charX + 1) * charWidth, (7 - charY) * charHeight,
             charX * charWidth, (8 - charY) * charHeight,
             (charX + 1) * charWidth, (8 - charY) * charHeight
        };

        // This will identify our vertex buffer
        shader.Bind();
        texture.Bind(shader);

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


        GLuint uvbuffer;
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);


        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &uvbuffer);
    }
}