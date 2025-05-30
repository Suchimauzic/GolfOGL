#ifndef GAME_HPP
#define GAME_HPP

#include "Core/Window.hpp"
#include "Core/Shader.hpp"
#include "Core/Renderer.hpp"

#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"

#include "Physics/Collider.hpp"

#include "Manager/TextureManager.hpp"
#include "Manager/ShaderManager.hpp"

#include "Player.hpp"
#include "FirstScene.hpp"

class Game
{
public:
    Game(int width, int height, const char* title);
    ~Game();
    
    void gameLoop();
    int getWindowStatus();

private:
    Window* window;
};

#endif