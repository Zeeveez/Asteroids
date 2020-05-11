#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine/Shader/Shader.h"

namespace Engine {
    class Texture {
        public:
            GLuint textureID = -1;
            Texture(const char* path);
            ~Texture();
            void Bind(Shader& shader, int textureUnit = 0);
    };
}

#endif