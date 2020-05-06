#ifndef TEXT_H
#define TEXT_H

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace Asteroids {
    void DrawString(Texture& texture, Shader& shader, float x, float y, float size, std::string str);
    void DrawCharacter(Texture& texture, Shader& shader, float x, float y, float size, char c);
}

#endif