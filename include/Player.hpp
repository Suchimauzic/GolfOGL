#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Primitives/Sphere.hpp"

#include "Gravity.hpp"
#include <string>

class Player
{
public:
    Player();
    Player(const float sphereRadius, const int sphereSectorCount, const int stackCount);
    ~Player();

    void update(const float& deltaTime);
    void loadShader(const std::string& shaderName);
    
    // Getters
    Sphere& getObject();

private:
    Sphere* sphere;
    Gravity* gravity;
};

#endif