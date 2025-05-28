#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Primitives/Sphere.hpp"

#include "Physics/Gravity.hpp"
#include "Physics/Collider.hpp"

#include <string>

enum class PlayerStatus
{
    FALL,
    STAY
};

class Player
{
public:
    Player();
    Player(const float sphereRadius, const int sphereSectorCount, const int stackCount);
    ~Player();

    void update(const float& deltaTime);
    void loadShader(const std::string& shaderName);

    bool isCollision(Object& object);
    
    // Setters
    void setStatus(PlayerStatus status);

    // Getters
    Sphere& getObject();
    Gravity& getGravity();
    PlayerStatus getStatus() const;

private:
    Sphere* sphere;
    Gravity* gravity;
    Collider* collider;

    PlayerStatus status;
};

#endif