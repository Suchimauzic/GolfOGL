#include "Manager/TextureManager.hpp"

std::vector<Texture2D> TextureManager::texture2DList = {};
std::vector<TextureCubemap> TextureManager::textureCubemapList = {};

void TextureManager::initTextureManager()
{
    // loadTexture("res/Textures/DefaultTexture.png", "default", TextureType::Cubemap);
    loadTexture("res/Textures/DefaultTexture2.png", "default", TextureType::Cubemap);
}

void TextureManager::loadTexture(const char* filepath, const std::string& textureName, TextureType textureType)
{
    if (textureType == TextureType::Sampler2D)
    {
        Texture2D texture(filepath, textureName);
        texture2DList.push_back(texture);
    }
    else if (textureType == TextureType::Cubemap)
    {
        TextureCubemap texture(filepath, textureName);
        textureCubemapList.push_back(texture);
    }
}

Texture2D TextureManager::getTexture2D(const std::string& textureName)
{
    for (Texture2D& texture : texture2DList)
    {
        if (texture.getName() == textureName)
        {
            return texture;
        }
    }

    return texture2DList[0];
}

TextureCubemap& TextureManager::getTextureCubemap(const std::string& textureName)
{
    for (TextureCubemap& texture : textureCubemapList)
    {
        if (texture.getName() == textureName)
        {
            return texture;
        }
    }

    return textureCubemapList[0];
}