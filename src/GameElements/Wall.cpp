#include "GameElements/Wall.hpp"

Wall::Wall()
    : GameElement(CollisionState::WALL),
    cube(new Cube())
{}

Wall::~Wall()
{
    delete cube;
}

void Wall::loadShader(const std::string& shaderName)
{
    cube->loadShader(shaderName);
}


// Setters
void Wall::setPosition(glm::vec3 position)
{
    cube->setPosition(position);
}

void Wall::setRotation(float angle, glm::vec3 rotation)
{
    cube->setRotation(angle, rotation);
}

void Wall::setSize(glm::vec3 size)
{
    cube->setSize(size);
}

void Wall::setCollisionState(CollisionState collisionState)
{
    this->collisionState = collisionState;
}


// Getters
glm::vec3 Wall::getPosition() const
{
    return cube->getPosition();
}

glm::vec3 Wall::getGlobalPosition() const
{
    return cube->getGlobalPosition();
}

glm::vec3 Wall::getRotation() const
{
    return cube->getRotation();
}

glm::vec3 Wall::getSize() const
{
    return cube->getSize();
}

CollisionState Wall::getCollisionState() const
{
    return collisionState;
}

Object& Wall::getObject()
{
    return *cube;
}