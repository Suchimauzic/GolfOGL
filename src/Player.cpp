#include "Player.hpp"

Player::Player()
{
    sphere = new Sphere(0.2f, 32, 32);
    gravity = new Gravity();
}

Player::Player(const float sphereRadius, const int sphereSectorCount, const int stackCount)
{
    sphere = new Sphere(sphereRadius, sphereSectorCount, stackCount);
    gravity = new Gravity();
}

Player::~Player()
{
    delete sphere;
    delete gravity;
}

void Player::update(const float& deltaTime)
{
    gravity->useGravity(*sphere, deltaTime);
}

void Player::loadShader(const std::string& shaderName)
{
    sphere->loadShader(shaderName);
}

Sphere& Player::getObject()
{
    return *sphere;
}