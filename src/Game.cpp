#include "Game.hpp"

Game::Game(int width, int height, const char* title)
{
    window = new Window(width, height, title);
}

Game::~Game()
{
    delete window;
}

void Game::gameLoop()
{
    Cube* cube = new Cube();
    Cube* place = new Cube();

    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    place->setSize(glm::vec3(10.0f, 0.0000001f, 10.0f));
    place->setPosition(glm::vec3(0.0f, -2.0f, 0.0f));

    cube->setPosition(glm::vec3(0.0f, 4.0f, 0.0f));
    

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
        
        place->render(window->camera, &shader, GameConfig::width, GameConfig::height);
        cube->render(window->camera, &shader, GameConfig::width, GameConfig::height);

        window->swapBuffers();

        // cube->setPosition((cube->getPosition() - glm::vec3(0.0f, 9.81f, 0.0f)) * window->getDeltaTime());
    }

    delete place;
    delete cube;
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}