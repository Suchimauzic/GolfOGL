#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Logger.hpp"

#include <string>

class Texture
{
public:
    Texture(const char* path, const std::string& name);
    ~Texture() = default;

    unsigned int loadTexture(const char* path);

    unsigned int getId() const;
    std::string getName() const;

private:
    unsigned int id;
    std::string name;
};

#endif