#ifndef GAME_HPP
#define GAME_HPP

#include "Core/Window.hpp"
#include "Core/Shader.hpp"
#include "Core/Renderer.hpp"

#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"

#include "Components/Collider.hpp"

#include "TextureManager.hpp"

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