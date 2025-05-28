#include "Player.hpp"

Player::Player()
    : status(PlayerStatus::FALL),
    sphere(new Sphere(0.2f, 32, 32)),
    gravity(new Gravity()),
    collider(new Collider())
{
    sphere->setSize(glm::vec3(1.0f, 2.0f, 1.0f));
}

Player::Player(const float sphereRadius, const int sphereSectorCount, const int stackCount)
    : status(PlayerStatus::FALL),
    sphere(new Sphere(sphereRadius, sphereSectorCount, stackCount)),
    gravity(new Gravity()),
    collider(new Collider())
{
    sphere->setSize(glm::vec3(1.0f, 2.0f, 1.0f));
}

Player::~Player()
{
    delete sphere;
    delete gravity;
    delete collider;
}

void Player::update(const float& deltaTime)
{
    if (status == PlayerStatus::FALL)
        gravity->useGravity(*sphere, deltaTime);
}

void Player::loadShader(const std::string& shaderName)
{
    sphere->loadShader(shaderName);
}

bool Player::isCollision(Object& object)
{
    return collider->isCollision(sphere->getWorldVertices(), object.getWorldVertices());
}

void Player::setStatus(PlayerStatus status)
{
    this->status = status;
}

Sphere& Player::getObject()
{
    return *sphere;
}

Gravity& Player::getGravity()
{
    return *gravity;
}

PlayerStatus Player::getStatus() const
{
    return status;
}