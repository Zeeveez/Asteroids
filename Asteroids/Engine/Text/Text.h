#ifndef TEXT_H
#define TEXT_H

#include "Engine/Shader/Shader.h"
#include "Engine/Texture/Texture.h"

namespace Engine {
    void DrawString(Texture& texture, Shader& shader, float x, float y, int size, std::string str);
    void DrawCharacter(Texture& texture, Shader& shader, float x, float y, float w, float h, char c);
}

#endif