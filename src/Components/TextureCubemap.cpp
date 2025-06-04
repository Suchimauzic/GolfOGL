#include "Components/TextureCubemap.hpp"

TextureCubemap::TextureCubemap(const char* path, const std::string& name)
    : Texture(name)
{
    id = loadTexture(path);
}

unsigned int TextureCubemap::loadTexture(const char* path)
{
    unsigned int textureId;
    int width, height, nrComponents;
    unsigned char* data;

    glGenTextures(1, &textureId);

    data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;

        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        }
    }
    else
    {
        Logger::printError("Texture failed to load path: " + *path);
    }

    stbi_image_free(data);

    return textureId;
}