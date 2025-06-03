#include "Game.hpp"

#include "GameElements/Item.hpp"

Game::Game(int width, int height, const char* title)
{
    window = new Window(width, height, title);

    ShaderManager::loadShader("res/shaders/CubeShader.vs", "res/shaders/CubeShader.fs", "CubeShader");
    ShaderManager::loadShader("res/shaders/SphereShader.vs", "res/shaders/SphereShader.fs", "SphereShader");
    ShaderManager::loadShader("res/shaders/LightShader.vs", "res/shaders/LightShader.fs", "LightShader");

    TextureManager::initTextureManager();
}

Game::~Game()
{
    delete window;
}

void Game::gameLoop()
{
    window->loadScene(new FirstScene());

    while (!window->isShouldClose())
    {
        // deltaTime
        window->updateDeltaTime( static_cast<float>(glfwGetTime()) );

        // Events
        window->pollEvents();
        window->proccessInput();

        // OpenGL
        glClearColor(0.76f, 0.45f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        window->render();

        window->swapBuffers();
    }

    window->removeScene();
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}