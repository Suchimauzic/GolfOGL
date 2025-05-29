#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <glm/glm.hpp>

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
    void setPosition(glm::vec3 position);
    void setRotation(float angle, glm::vec3 rotation);
    void setSize(glm::vec3 size);
    void setSpeed(float speed);

    // Getters
    Sphere& getObject();
    Gravity& getGravity();
    PlayerStatus getStatus() const;
    glm::vec3 getPosition();
    float getSpeed();

private:
    Sphere* sphere;
    Gravity* gravity;
    Collider* collider;

    float speed;

    PlayerStatus status;
};

#endif