#include "Text.h"
#include <sstream>
#include <vector>
#include "Engine/Options/Options.h"

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

        void DrawString(Texture& texture, Shader& shader, Anchor anchor, float x, float y, float size, std::string str) {
            std::vector<std::string> strings = SplitString(str, '\n');
            // characterNo, lineNo, char
            std::vector<GLint> textDataBufferData = {};
            int lineNo = 0;
            for (auto& str : strings) {
                int charNo = 0;
                for (auto& c : str) {
                    textDataBufferData.push_back(charNo++);
                    textDataBufferData.push_back(lineNo);
                    textDataBufferData.push_back(c);
                }
                lineNo++;
            }

            GLuint VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            static const GLfloat characterVertexBufferData[] = {
                 0.0f, 0.0f,
                 0.0625f, 0.0f,
                 0.0f, -0.125f,
                 0.0625f, -0.125f
            };
            // TODO: Redo anchoring position (only current works as a top left anchor
            shader.Bind();
            texture.Bind(shader);
            glUniform2f(glGetUniformLocation(shader.program, "res"), Engine::Options::screenSize.first, Engine::Options::screenSize.second);
            glUniform3f(glGetUniformLocation(shader.program, "anchorSize"), x, y, size);

            GLuint characterVertexBuffer;
            glGenBuffers(1, &characterVertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, characterVertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(characterVertexBufferData), characterVertexBufferData, GL_STATIC_DRAW);

            // vert pos's
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
            glVertexAttribDivisor(0, 0);

            GLuint textDataBuffer;
            glGenBuffers(1, &textDataBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, textDataBuffer);
            glBufferData(GL_ARRAY_BUFFER, textDataBufferData.size() * sizeof(GLint), textDataBufferData.data(), GL_DYNAMIC_DRAW);

            // characterNo, lineNo, char
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, 3 * sizeof(GLint), (void*)0);
            glVertexAttribDivisor(1, 1);

            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, textDataBufferData.size() / 3);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDeleteBuffers(1, &textDataBuffer);
            glDeleteBuffers(1, &characterVertexBuffer);

            glBindVertexArray(0);
            glDeleteVertexArrays(1, &VAO);
        }
    }
}