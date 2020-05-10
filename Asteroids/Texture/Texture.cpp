#include "Texture.h"

#include <vector>
#include <iterator>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Asteroids {
    Texture::Texture(const char* path) {
        std::ifstream f(path, std::ios::binary);

        uint32_t fileID;
        f.read(reinterpret_cast<char*>(&fileID), sizeof(fileID));
        std::cout << (fileID == 0x20534444);    // "DDS "


        uint32_t height;
        uint32_t width;
        uint32_t linearSize;
        uint32_t mipMapCount;
        uint32_t fourCC;
        f.seekg(12);
        f.read(reinterpret_cast<char*>(&height), sizeof(height));
        f.read(reinterpret_cast<char*>(&width), sizeof(width));
        f.read(reinterpret_cast<char*>(&linearSize), sizeof(linearSize));
        f.seekg(28);
        f.read(reinterpret_cast<char*>(&mipMapCount), sizeof(mipMapCount));
        f.seekg(84);
        f.read(reinterpret_cast<char*>(&fourCC), sizeof(fourCC));

        f.unsetf(std::ios::skipws);
        uint32_t bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
        std::vector<unsigned char> buffer;
        f.seekg(128);
        buffer.reserve(bufsize);
        buffer.insert(buffer.begin(),
            std::istream_iterator<unsigned char>(f),
            std::istream_iterator<unsigned char>());
        f.close();

        unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
        unsigned int format;
        switch (fourCC) {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            return;
        }

        // Create one OpenGL texture
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
        unsigned int offset = 0;

        /* load the mipmaps */
        for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
            unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
            glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                0, size, &buffer[offset]);

            offset += size;
            width /= 2;
            height /= 2;
        }
    }

    Texture::~Texture() {
        glDeleteTextures(1, &textureID);
    }

    void Texture::Bind(Shader& shader, int textureUnit) {
        // TODO : Allow binding actual active texture from textureUnit
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(glGetUniformLocation(shader.program, "textureID"), textureUnit);
    }
}