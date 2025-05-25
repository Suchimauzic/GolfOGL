#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "Primitives/Object.hpp"

class Gravity
{
public:
    Gravity(const float maxVelocity = 10.0f, const bool isActiveGravity = true);
    ~Gravity() = default;

    void useGravity(Object& object, const float& deltaTime);

private:
    const float gravity = -9.81f;

    float velocity;
    float maxVelocity;
    bool isActiveGravity;
};

#endif