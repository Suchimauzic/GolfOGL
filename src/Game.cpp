#include "Game.hpp"

#include "Components/Collider.hpp"

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
    // Cube* cube = new Cube();
    Cube* place = new Cube();
    Sphere* sphere = new Sphere(1, 30, 30);

    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    place->setSize(glm::vec3(10.0f, 0.01f, 10.0f));
    place->setPosition(glm::vec3(0.0f, -2.0f, 0.0f));

    sphere->setSize(glm::vec3(0.4f, 0.4f, 0.4f));
    sphere->setPosition(glm::vec3(0.0f, 15.0f, 0.0f));

    // cube->setPosition(glm::vec3(0.0f, 4.0f, 0.0f));

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

        place->render(window->getCamera(), &shader, GameConfig::width, GameConfig::height);
        // cube->render(window->getCamera(), &shader, GameConfig::width, GameConfig::height);
        sphere->render(window->getCamera(), &shader, GameConfig::width, GameConfig::height);

        window->swapBuffers();

        // std::vector<glm::vec3> worldCubePos = cube->getWorldVertices();
        std::vector<glm::vec3> worldPlacePos = place->getWorldVertices();
        std::vector<glm::vec3> worldSpherePos = sphere->getWorldVertices();

        if (!collider.isCollision(worldSpherePos, worldPlacePos))
            sphere->setPosition((sphere->getPosition() - glm::vec3(0.0f, 9.81f, 0.0f)) * window->getDeltaTime());
    }

    delete place;
    // delete cube;
    delete sphere;
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}