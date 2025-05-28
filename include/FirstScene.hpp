#ifndef FIRSTSCENE_HPP
#define FIRSTSCENE_HPP

#include "Core/Renderer.hpp"
#include "Primitives/Cube.hpp"

#include "GameElements/GameElement.hpp"
#include "Player.hpp"

#include <vector>

class FirstScene
{
public:
    FirstScene();
    ~FirstScene();

private:
    void generateLevel();
    void loadShader();
    void loadRenderer();
    
    Player* player;
    std::vector<Object*> levelObjects;
};

#endif