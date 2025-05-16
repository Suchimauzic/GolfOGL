#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "Core/Window.hpp"
#include "Core/Shader.hpp"
#include "Core/Logger.hpp"

#include "Game.hpp"
#include "GameConfig.hpp"
#include "Camera.hpp"


#include "Primitives/Object.hpp"
#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"

int main()
{
    Game game(1280, 720, "GolfOGL");
    
    int windowCodeStatus = game.getWindowStatus();
    
    if (windowCodeStatus)
        return windowCodeStatus;
    
    game.gameLoop();

    return 0;
}