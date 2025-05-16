#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Components/Texture.hpp"
#include "Logger.hpp"

#include <string>

class Texture2D : public Texture
{
public:
    Texture2D(const char* path, const std::string& name);
    ~Texture2D() = default;
    
    unsigned int loadTexture(const char* path) override;
};

#endif