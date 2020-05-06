#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Shader/Shader.h"

namespace Asteroids {
    class Texture {
        public:
            GLuint textureID = -1;
            Texture(const char* path);
            ~Texture();
            void Bind(Shader& shader, int textureUnit = 0);
    };
}

#endif