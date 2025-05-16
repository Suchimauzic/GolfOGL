#ifndef TEXTURECUBEMAP_HPP
#define TEXTURECUBEMAP_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include "Components/Texture.hpp"
#include "Logger.hpp"

#include <string>

class TextureCubemap : public Texture
{
public:
    TextureCubemap(const char* path, const std::string& name);

    unsigned int loadTexture(const char* path) override;
};

#endif