#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Core/Logger.hpp"

#include <string>

class Texture
{
public:
    virtual unsigned int loadTexture(const char* path) = 0;

    unsigned int getId() const;
    std::string getName() const;

protected:
    unsigned int id;
    std::string name;

    Texture(const std::string& name);
    virtual ~Texture() = default;
};

#endif