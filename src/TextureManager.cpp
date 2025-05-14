#include "TextureManager.hpp"

std::vector<Texture> TextureManager::textureList = {};

void TextureManager::initTextureManager()
{
    loadTexture("res/Textures/DefaultTexture.png", "default");
}

void TextureManager::loadTexture(const char* filepath, const std::string& textureName)
{
    Texture texture(filepath, textureName);
    textureList.push_back(texture);
}

Texture TextureManager::getTexture(const std::string textureName)
{
    for (Texture& texture : textureList)
    {
        if (texture.getName() == textureName)
        {
            return texture;
        }
    }

    return textureList[0];
}