#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "Primitives/Object.hpp"
#include <cmath>
#include <glm/glm.hpp>

class Gravity
{
public:
    Gravity(const float maxVelocity = 100.0f, const bool isActiveGravity = true);
    ~Gravity() = default;

    void useGravity(Object& object, const float& deltaTime);

    // Setters
    void setVelocity(float velocity);
    
    // Getters
    float getVelocity() const;

private:
    const float gravity = -9.81f;

    float velocity;
    float maxVelocity;
    bool isActiveGravity;
};

#endif