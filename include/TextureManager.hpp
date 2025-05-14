#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Components/Texture.hpp"

#include <vector>
#include <string>

class TextureManager
{
public:
    static void initTextureManager();
    static void loadTexture(const char* filepath, const std::string& textureName);
    static Texture getTexture(const std::string textureName);

private:
    static std::vector<Texture> textureList;
};

#endif