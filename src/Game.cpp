#include "Game.hpp"

#include "Player.hpp"

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
    Cube* cube = new Cube();
    Player* player = new Player();

    Renderer renderer;
    renderer.addObject(*cube);
    renderer.addObject(player->getObject());

    ShaderManager::loadShader("res/shaders/CubeShader.vs", "res/shaders/CubeShader.fs", "CubeShader");
    ShaderManager::loadShader("res/shaders/SphereShader.vs", "res/shaders/SphereShader.fs", "SphereShader");

    cube->loadShader("CubeShader");
    player->loadShader("CubeShader");

    cube->setSize(glm::vec3(1.0f, 0.5f, 1.0f));

    player->getObject().setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

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

        renderer.draw(window->getCamera());

        window->swapBuffers();

        std::vector<glm::vec3> worldCube = cube->getWorldVertices();

        player->update(window->getDeltaTime());
    }

    delete cube;
    delete player;
}

int Game::getWindowStatus()
{
    return window->getCodeStatus();
}