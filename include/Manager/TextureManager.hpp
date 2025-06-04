#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Components/Texture.hpp"
#include "Components/Texture2D.hpp"
#include "Components/TextureCubemap.hpp"

#include <vector>
#include <string>

enum class TextureType
{
    Sampler2D,
    Cubemap
};

class TextureManager
{
public:
    static void initTextureManager();
    static void loadTexture(const char* filepath, const std::string& textureName, TextureType textureType);
    static Texture2D getTexture2D(const std::string& textureName);
    static TextureCubemap& getTextureCubemap(const std::string& textureName);

private:
    static std::vector<TextureCubemap> textureCubemapList;
    static std::vector<Texture2D> texture2DList;
};

#endif