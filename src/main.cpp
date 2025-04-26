#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "Game.hpp"
#include "Window.hpp"
#include "GameConfig.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include "Objects/Object.hpp"
#include "Objects/Cube.hpp"
#include "Objects/Sphere.hpp"

int main()
{
    Game game(1280, 720, "GolfOGL");
    
    int windowCodeStatus = game.getWindowStatus();
    
    if (windowCodeStatus)
        return windowCodeStatus;
    
    game.gameLoop();

    return 0;
}