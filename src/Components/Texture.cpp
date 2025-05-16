#include "Components/Texture.hpp"

Texture::Texture(const std::string& name)
    : id(0),
    name(name)
{}

unsigned int Texture::getId() const
{
    return id;
}

std::string Texture::getName() const
{
    return name;
}