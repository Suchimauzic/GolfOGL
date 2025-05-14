#include "Game.hpp"

Game::Game(int width, int height, const char* title)
{
    window = new Window(width, height, title);

    TextureManager::initTextureManager();
}

Game::~Game()
{
    delete window;
}

void Game::gameLoop()
{
    Sphere* sphere = new Sphere(1, 32, 32);
    Cube* cube = new Cube();

    TextureManager::loadTexture("res/Textures/GolfBallTexture.jpg", "GolfBall");
    sphere->loadTexture("GolfBall");

    Renderer renderer;
    renderer.addObject(*sphere);
    renderer.addObject(*cube);

    Shader shader("res/shaders/SphereShader.vs", "res/shaders/SphereShader.fs");

    sphere->setSize(glm::vec3(0.2f, 0.2f, 0.2f));
    sphere->setPosition(glm::vec3(0.0f, 15.0f, 0.0f));

    Collider collider;

    while (!window->isShouldClose())
    {
        // deltaTime
        window->updateDeltaTime( static_cast<float>(glfwGetTime()) );

        // Events
        window->pollEvents();
        window->proccessInput();

        // OpenGL
        glClearColor(0.6f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        renderer.draw(window->getCamera(), &shader);

        window->swapBuffers();
    }

    delete cube;
    delete sphere;
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}