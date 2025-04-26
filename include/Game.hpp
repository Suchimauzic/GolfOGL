#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"
#include "Objects/Cube.hpp"
#include "Objects/Sphere.hpp"
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