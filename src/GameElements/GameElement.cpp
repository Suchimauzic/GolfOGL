#include "GameElements/GameElement.hpp"

GameElement::GameElement()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = 0.0f;
}

GameElement::~GameElement()
{
    for (Object* object : objects)
    {
        Renderer::removeObject(*object);
        delete object;
    }
}

void GameElement::loadShader(const std::string& shaderName)
{
    for (Object* object : objects)
    {
        object->loadShader(shaderName);
    }
}

void GameElement::loadRenderer()
{
    for (Object* object : objects)
    {
        Renderer::addObject(*object);
    }
}

void GameElement::setPosition(glm::vec3 position)
{
    this->position = position;
}

void GameElement::setRotation(float rotation)
{
    this->rotation = rotation;
}