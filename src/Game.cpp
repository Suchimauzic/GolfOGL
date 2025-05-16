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

    Renderer renderer;
    renderer.addObject(*sphere);
    renderer.addObject(*cube);

    ShaderManager::loadShader("res/shaders/CubeShader.vs", "res/shaders/CubeShader.fs", "CubeShader");

    sphere->setSize(glm::vec3(0.2f, 0.2f, 0.2f));
    sphere->setPosition(glm::vec3(0.0f, -5.0f, 0.0f));

    cube->setSize(glm::vec3(1.0f, 0.5f, 1.0f));

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

        renderer.draw(window->getCamera(), &ShaderManager::getShader("CubeShader"));

        window->swapBuffers();

        std::vector<glm::vec3> worldSphere = sphere->getWorldVertices();
        std::vector<glm::vec3> worldCube = cube->getWorldVertices();

        if (collider.isCollision(worldSphere, worldCube))
            Logger::printInfo("Collision detected");
        else
            Logger::printInfo("Collision is not detected");

        sphere->setPosition(glm::vec3(0.0f, sin(glfwGetTime()) * 5.0f * window->getDeltaTime(), 0.0f));
    }

    delete cube;
    delete sphere;
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}