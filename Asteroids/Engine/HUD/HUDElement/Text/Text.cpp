#include "Text.h"
#include <sstream>
#include <vector>

namespace Engine {
    namespace Text {
        std::vector<std::string> SplitString(std::string str, char delimiter) {
            std::vector<std::string> out = {};
            std::stringstream ss(str);
            std::string s;
            while (getline(ss, s, delimiter)) {
                out.push_back(s);
            }
            return out;
        }

        void DrawString(Texture& texture, Shader& shader, Anchor anchor, float x, float y, int size, std::string str) {
            int w;
            int h;
            glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
            float charHeight = size * 2.0f / h;
            float charWidth = size * 1.0f / w;

            std::vector<std::string> strings = SplitString(str, '\n');

            int yIndex = 0;
            for (const auto& line : strings) {
                float yPos = 0;
                switch (anchor) {
                case Anchor::TOP_LEFT: case Anchor::TOP_CENTER: case Anchor::TOP_RIGHT:
                    yPos = y - charHeight * ++yIndex;
                    break;
                case Anchor::MIDDLE_LEFT: case Anchor::MIDDLE_CENTER: case Anchor::MIDDLE_RIGHT:
                    yPos = y + ((float)strings.size() / 2 - ++yIndex) * charHeight;
                    break;
                case Anchor::BOTTOM_LEFT: case Anchor::BOTTOM_CENTER: case Anchor::BOTTOM_RIGHT:
                    yPos = y + (strings.size() - ++yIndex) * charHeight;
                    break;
                }

                int xIndex = 0;
                for (const auto& c : line) {
                    float xPos = 0;
                    switch (anchor) {
                    case Anchor::TOP_LEFT: case Anchor::MIDDLE_LEFT: case Anchor::BOTTOM_LEFT:
                        xPos = x + charWidth * xIndex++;
                        break;
                    case Anchor::TOP_CENTER: case Anchor::MIDDLE_CENTER: case Anchor::BOTTOM_CENTER:
                        xPos = x - ((float)line.length() / 2 - xIndex++) * charWidth;
                        break;
                    case Anchor::TOP_RIGHT: case Anchor::MIDDLE_RIGHT: case Anchor::BOTTOM_RIGHT:
                        xPos = x - (line.length() - xIndex++) * charWidth;
                        break;
                    }
                    DrawCharacter(texture, shader, xPos, yPos, charWidth, charHeight, c);
                }
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
}