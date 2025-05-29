#include "FirstScene.hpp"

FirstScene::FirstScene()
{
    generateLevel();
    loadShader();
    loadRenderer();
}

FirstScene::~FirstScene()
{
    Renderer::removeObject(player->getObject());

    delete player;
    delete camera;

    for (Object* object : levelObjects)
    {
        Renderer::removeObject(*object);
        delete object; 
    }
}

void FirstScene::processInput(GLFWwindow* window, float deltaTime)
{
    float speed = player->getSpeed() * deltaTime;
    glm::vec3 moveDirection(0.0f);

    // Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        moveDirection.z -= 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        moveDirection.z += 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        moveDirection.x -= 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        moveDirection.x += 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }


    // Speed calculation

    glm::vec3 playerNewPosition = player->getPosition();

    // Need to move a player, now he's not move
    // Maybe the player needs his own shader

    if (moveDirection.x != 0.0f || moveDirection.z != 0.0f)
    {
        moveDirection = glm::normalize(moveDirection) * speed;
        playerNewPosition = player->getPosition() + moveDirection;
        player->setPosition(playerNewPosition);
    }

    camera->setPosition(playerNewPosition + glm::vec3(0.0f, 3.0f, 2.0f), deltaTime);
}

Camera& FirstScene::getCamera()
{
    return *camera;
}

void FirstScene::loadShader()
{
    player->loadShader("CubeShader");

    for (Object* object : levelObjects)
    {
        object->loadShader("CubeShader");
    }
}

void FirstScene::loadRenderer()
{
    Renderer::addObject(player->getObject());

    for (Object* object : levelObjects)
    {
        Renderer::addObject(*object);
    }
}

void FirstScene::generateLevel()
{
    player = new Player();
    player->setPosition(glm::vec3(-4.5f, -0.25f, 4.5f));

    camera = new Camera(glm::vec3(-4.5f, 2.25f, 6.0f));
    camera->setPitch(-60.0f);

    // Floor
    Cube* cube = new Cube();
    cube->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    cube->setSize(glm::vec3(10.5f, 0.1f, 10.5f));
    levelObjects.push_back(cube);

    // Level wall
    // Left
    cube = new Cube();
    cube->setPosition(glm::vec3(-5.0f, -0.5f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 10.1f));
    levelObjects.push_back(cube);

    // Back
    cube = new Cube();
    cube->setPosition(glm::vec3(0.0f, -0.5f, -5.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 9.9f));
    levelObjects.push_back(cube);

    // Right
    cube = new Cube();
    cube->setPosition(glm::vec3(5.0f, -0.5f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 10.1f));
    levelObjects.push_back(cube);
    
    // Front
    cube = new Cube();
    cube->setPosition(glm::vec3(0.0f, -0.5f, 5.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 9.9f));
    levelObjects.push_back(cube);


    // Labyrinth

    /*
    Level
     = = = = = = = f = =  
    |_   _   _ _  |_ _  |
    | | | | |_  | |  _  |
    | | | |_ _ _|  _| | |    
    |_ _|_   _ _ _| | | |    
    |  _ _|  _ _  | |_ _|
    | |  _ _  |  _| | | |
    | | |   | |  _  |_| |
    |_ _| | |_| | |_   _|    
    |  _ _|_   _|_ _| | |
    | |     |       | | |
     s = = = = = = = = = 

        s - start
        f - finish
    */

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.0f, -0.5f, 4.45f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.5f, -0.5f, 4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.5f, -0.5f, 4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.5f, -0.5f, 4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.0f, -0.5f, 4.45f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.0f, -0.5f, 3.45f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.0f, -0.5f, 2.45f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.45f, -0.5f, 3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.50f, -0.5f, 3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.0f, -0.5f, 2.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.0f, -0.5f, 1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.45f, -0.5f, 1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.5f, -0.5f, 1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.0f, -0.5f, 1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.0f, -0.5f, 2.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-0.5f, -0.5f, 3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(0.0f, -0.5f, 2.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);
    
    cube = new Cube();
    cube->setPosition(glm::vec3(0.0f, -0.5f, 1.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(0.0f, -0.5f, 0.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-0.5f, -0.5f, 0.05f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(0.5f, -0.5f, 0.05f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);


    cube = new Cube();
    cube->setPosition(glm::vec3(0.5f, -0.5f, 4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.5f, -0.5f, 4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.5f, -0.5f, 4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.0f, -0.5f, 3.45f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.0f, -0.5f, 2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.5f, -0.5f, 2.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);
    
    cube = new Cube();
    cube->setPosition(glm::vec3(2.0f, -0.5f, 2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.45f, -0.5f, 3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.05f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.95f, -0.5f, 3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.95f, -0.5f, 4.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, 4.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, 3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.5f, -0.5f, 3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, 1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, 0.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.5f, -0.5f, 0.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.5f, -0.5f, 0.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.5f, -0.5f, 2.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.0f, -0.5f, 1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.0f, -0.5f, 0.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.0f, -0.5f, -0.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.0f, -0.5f, -1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.0f, -0.5f, -2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.5f, -0.5f, -3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, -1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, -2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(3.55f, -0.5f, -4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.5f, -0.5f, -4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.0f, -0.5f, -4.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.0f, -0.5f, -3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.5f, -0.5f, -2.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.0f, -0.5f, -1.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.0f, -0.5f, -0.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(2.0f, -0.5f, 0.55f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.5f, -0.5f, 1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.5f, -0.5f, -1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(0.5f, -0.5f, -1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-0.5f, -0.5f, -1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.5f, -0.5f, -1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.5f, -0.5f, -1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.5f, -0.5f, -1.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.0f, -0.5f, -0.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.5f, -0.5f, 0.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.5f, -0.5f, 0.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.0f, -0.5f, 0.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.0f, -0.5f, 1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.0f, -0.5f, -1.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.0f, -0.5f, -2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-3.0f, -0.5f, -3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.0f, -0.5f, -2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.0f, -0.5f, -3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-4.5f, -0.5f, -4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.5f, -0.5f, -4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.0f, -0.5f, -3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-2.0f, -0.5f, -2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.5f, -0.5f, -2.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-0.5f, -0.5f, -2.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(0.5f, -0.5f, -2.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.0f, -0.5f, -2.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(1.0f, -0.5f, -3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-1.0f, -0.5f, -3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(0.5f, -0.5f, -4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-0.5f, -0.5f, -4.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(-0.5f, -0.5f, -3.0f));
    cube->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    levelObjects.push_back(cube);
}