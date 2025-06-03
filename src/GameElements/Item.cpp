#include "GameElements/Item.hpp"

Item::Item()
    : GameElement(CollisionState::ITEM),
    sphere(new Sphere(0.1f, 16, 16))
{}

Item::~Item()
{
    delete sphere;
}

void Item::loadShader(const std::string& shaderName)
{
    sphere->loadShader(shaderName);
}


// Setters
void Item::setPosition(glm::vec3 position)
{
    sphere->setPosition(position);
}

void Item::setRotation(float angle, glm::vec3 rotation)
{
    sphere->setRotation(angle, rotation);
}

void Item::setSize(glm::vec3 size)
{
    sphere->setSize(size);
}

void Item::setCollisionState(CollisionState collisionState)
{
    this->collisionState = collisionState;
}

void Item::setColor(const std::string& colorName, const glm::vec3& color)
{
    sphere->setColor(colorName, color);
}


// Getters
glm::vec3 Item::getPosition() const
{
    return sphere->getPosition();
}

glm::vec3 Item::getGlobalPosition() const
{
    return sphere->getGlobalPosition();
}

glm::vec3 Item::getRotation() const
{
    return sphere->getRotation();
}

glm::vec3 Item::getSize() const
{
    return sphere->getSize();
}

CollisionState Item::getCollisionState() const
{
    return collisionState;
}

Object& Item::getObject()
{
    return *sphere;
}