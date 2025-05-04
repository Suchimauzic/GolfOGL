#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"
#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"
#include "Shader.hpp"

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