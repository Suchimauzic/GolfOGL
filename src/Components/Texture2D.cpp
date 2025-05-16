#include "Components/Texture2D.hpp"

Texture2D::Texture2D(const char* path, const std::string& name)
    : Texture(name)
{
    id = loadTexture(path);
}

unsigned int Texture2D::loadTexture(const char* path)
{
    unsigned int textureId;
    int width, height, nrComponents;
    unsigned char* data;

    glGenTextures(1, &textureId);
    
    data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        // Texture format
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

        // Texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        Logger::printError("Texture failed to load path: " + *path);
    }

    stbi_image_free(data);

    return textureId;
}

