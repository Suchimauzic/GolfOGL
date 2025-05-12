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
    Sphere* sphere = new Sphere(1, 32, 32);
    // Cube* place = new Cube();

    Renderer renderer;
    // renderer.addObject(*place);
    renderer.addObject(*sphere);

    Shader shader("res/shaders/shader.vs", "res/shaders/shader.fs");

    // place->setSize(glm::vec3(10.0f, 0.01f, 10.0f));
    // place->setPosition(glm::vec3(0.0f, -2.0f, 0.0f));

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

        // std::vector<glm::vec3> worldPlacePos = place->getWorldVertices();
        // std::vector<glm::vec3> worldSpherePos = sphere->getWorldVertices();

    //     if (!collider.isCollision(worldSpherePos, worldPlacePos))
    //     {
    //         sphere->setPosition((sphere->getPosition() - glm::vec3(0.0f, 9.81f, 0.0f)) * window->getDeltaTime());
    //     }
    }

    // delete place;
    delete sphere;
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}