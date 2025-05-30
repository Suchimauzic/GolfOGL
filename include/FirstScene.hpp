#ifndef FIRSTSCENE_HPP
#define FIRSTSCENE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Renderer.hpp"
#include "Core/Logger.hpp"

#include "Primitives/Cube.hpp"

#include "Player.hpp"
#include "Camera.hpp"

#include <vector>

class FirstScene
{
public:
    FirstScene();
    ~FirstScene();

    void processInput(GLFWwindow* window, float deltaTime);

    void checkCollision();
    Camera& getCamera();

private:
    void generateLevel();
    void loadShader();
    void loadRenderer();
    
    Player* player;
    Camera* camera;
    std::vector<Object*> levelObjects;
};

#endif