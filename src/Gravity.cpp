#include "Gravity.hpp"

Gravity::Gravity(const float maxVelocity, const bool isActiveGravity)
    : velocity(0),
    maxVelocity(maxVelocity),
    isActiveGravity(isActiveGravity)
{}

void Gravity::useGravity(Object& object, const float& deltaTime)
{
    velocity += 15.0f * gravity * deltaTime;
    
    if (velocity > maxVelocity)
    {
        velocity = maxVelocity * deltaTime;
    }

    object.setPosition((object.getPosition() + glm::vec3(0.0f, velocity, 0.0f) * deltaTime) * deltaTime);
}