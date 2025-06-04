#include "FirstScene.hpp"

FirstScene::FirstScene()
{
    generateLevel();
    loadShader();
    loadRenderer();

    item->setColor("lightColor", glm::vec3(0.24f, 0.67f, 0.24f));
}

FirstScene::~FirstScene()
{
    Renderer::removeObject(player->getObject());
    
    delete player;
    delete camera;

    for (GameElement* gameElement : gameElements)
    {
        Renderer::removeObject(gameElement->getObject());
        delete gameElement;
    }
}

void FirstScene::processInput(GLFWwindow* window, float deltaTime)
{
    // Close the game
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    float speed = player->getSpeed();
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

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = player->getSpeed() + 10.0f;
    }

    // Speed calculation

    glm::vec3 playerNewPosition = glm::vec3(0.0f);

    if (moveDirection.x != 0.0f || moveDirection.z != 0.0f)
    {
        // Calculation a new position
        moveDirection = glm::normalize(moveDirection) * speed;
        playerNewPosition = (player->getPosition() + moveDirection) * deltaTime;
        player->setPosition(playerNewPosition);
        
        // Check collision
        checkCollision(window);

        // Set a camera position relative to a player's global position
        camera->setPosition(player->getObject().getGlobalPosition());
    }
}

void FirstScene::checkCollision(GLFWwindow* window)
{
    glm::vec3 normal;
    float penetration;

    for (GameElement* gameElement : gameElements)
    {
        if (gameElement->getCollisionState() == CollisionState::NONE)
        {
            continue;
        }

        if (glm::distance(player->getGlobalPosition(), gameElement->getGlobalPosition()) > 1.5f)
        {
            continue;
        }
        
        if (gameElement->getCollisionState() == CollisionState::ITEM)
        {
            if (player->isCollision(gameElement->getObject()))
            {
                collisionItem(window);
            }
        }
        else
        {
            if (player->isCollision(gameElement->getObject(), normal, penetration))
            {
                normal = glm::vec3(0.0f);
                penetration = 0.0f;
                player->setPosition(-player->getPosition() + normal * penetration);
            }
        }
    }
}

void FirstScene::collisionItem(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, 1);
}

Camera& FirstScene::getCamera()
{
    return *camera;
}

void FirstScene::loadShader()
{
    player->loadShader("CubeShader");

    for (GameElement* gameElement : gameElements)
    {
        if (gameElement->getCollisionState() == CollisionState::ITEM)
        {
            gameElement->loadShader("LightShader");
        }
        else
        {
            gameElement->loadShader("CubeShader");
        }
    }
}

void FirstScene::loadRenderer()
{
    Renderer::addObject(player->getObject());

    for (GameElement* gameElement : gameElements)
    {
        Renderer::addObject(gameElement->getObject());
    }
}

void FirstScene::generateLevel()
{
    player = new Player();
    player->setPosition(glm::vec3(-4.5f, -0.25f, 4.5f));

    camera = new Camera();
    camera->setCameraOffset(glm::vec3(0.0f, 2.2f, 1.3f));
    camera->setPosition(player->getObject().getGlobalPosition());
    camera->setPitch(-60.0f);

    item = new Item();
    item->setPosition(glm::vec3(2.5f, -0.5f, -4.5f));
    item->setSize(glm::vec3(1.0f));
    gameElements.push_back(item);

    // Floor
    Wall* floor = new Wall();
    floor->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    floor->setSize(glm::vec3(10.5f, 0.1f, 10.5f));
    floor->setCollisionState(CollisionState::NONE);
    gameElements.push_back(floor);

    Wall* wall;
    // Level wall

    // Left
    for (int i = 0; i < 10; ++i)
    {
        wall = new Wall();

        if (i % 2 == 0)
        {
            wall->setPosition(glm::vec3(-5.0f, -0.5f, -4.5f + static_cast<float>(i)));
            wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
        }
        else
        {
            wall->setPosition(glm::vec3(-5.0f, -0.5f, -4.5f + static_cast<float>(i)));
            wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
        }

        gameElements.push_back(wall);
    }


    // Back
    for (int i = 0; i < 10; ++i)
    {
        wall = new Wall();

        if (i % 2 == 0)
        {
            wall->setPosition(glm::vec3(-4.5f + static_cast<float>(i), -0.5f, -5.0f));
            wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
        }
        else
        {
            wall->setPosition(glm::vec3(-4.5f + static_cast<float>(i), -0.5f, -5.0f));
            wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
        }
        
        gameElements.push_back(wall);
    }
    
    // Right
    for (int i = 0; i < 10; ++i)
    {
        wall = new Wall();

        if (i % 2 == 0)
        {
            wall->setPosition(glm::vec3(5.0f, -0.5f, -4.5f + static_cast<float>(i)));
            wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
            
        }
        else
        {
            wall->setPosition(glm::vec3(5.0f, -0.5f, -4.5f + static_cast<float>(i)));
            wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
        }

        gameElements.push_back(wall);
    }
    
    // Front
    for (int i = 0; i < 10; ++i)
    {
        wall = new Wall();

        if (i % 2 == 0)
        {
            wall->setPosition(glm::vec3(-4.5f + static_cast<float>(i), -0.5f, 5.0f));
            wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
        }
        else
        {
            wall->setPosition(glm::vec3(-4.5f + static_cast<float>(i), -0.5f, 5.0f));
            wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
        }
        
        gameElements.push_back(wall);
    }


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

    // wall = new Wall();
    // wall->setPosition(glm::vec3(2.5f, -0.5f, -4.5f));
    // wall->setSize(glm::vec3(0.2f, 0.2f, 0.2f));
    // walls.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.0f, -0.5f, 4.45f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.5f, -0.5f, 4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.5f, -0.5f, 4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.5f, -0.5f, 4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.0f, -0.5f, 4.45f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.0f, -0.5f, 3.45f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.0f, -0.5f, 2.45f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.45f, -0.5f, 3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.50f, -0.5f, 3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.0f, -0.5f, 2.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.0f, -0.5f, 1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.45f, -0.5f, 1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.5f, -0.5f, 1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.0f, -0.5f, 1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.0f, -0.5f, 2.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-0.5f, -0.5f, 3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(0.0f, -0.5f, 2.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);
    
    wall = new Wall();
    wall->setPosition(glm::vec3(0.0f, -0.5f, 1.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(0.0f, -0.5f, 0.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-0.5f, -0.5f, 0.05f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(0.5f, -0.5f, 0.05f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);


    wall = new Wall();
    wall->setPosition(glm::vec3(0.5f, -0.5f, 4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.5f, -0.5f, 4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.5f, -0.5f, 4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.0f, -0.5f, 3.45f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.0f, -0.5f, 2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.5f, -0.5f, 2.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);
    
    wall = new Wall();
    wall->setPosition(glm::vec3(2.0f, -0.5f, 2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.45f, -0.5f, 3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.05f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.95f, -0.5f, 3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.95f, -0.5f, 4.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.0f, -0.5f, 4.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.0f, -0.5f, 3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.5f, -0.5f, 3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.0f, -0.5f, 1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.0f, -0.5f, 0.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.5f, -0.5f, 0.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.5f, -0.5f, 0.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.5f, -0.5f, 2.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.0f, -0.5f, 1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.0f, -0.5f, 0.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.0f, -0.5f, -0.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.0f, -0.5f, -1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.0f, -0.5f, -2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.5f, -0.5f, -3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.0f, -0.5f, -1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(4.0f, -0.5f, -2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(3.55f, -0.5f, -4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.5f, -0.5f, -4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.0f, -0.5f, -4.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.0f, -0.5f, -3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.5f, -0.5f, -2.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.0f, -0.5f, -1.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.0f, -0.5f, -0.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(2.0f, -0.5f, 0.55f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.5f, -0.5f, 1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.5f, -0.5f, -1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(0.5f, -0.5f, -1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-0.5f, -0.5f, -1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.5f, -0.5f, -1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.5f, -0.5f, -1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.5f, -0.5f, -1.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.0f, -0.5f, -0.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.5f, -0.5f, 0.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.5f, -0.5f, 0.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.0f, -0.5f, 0.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.0f, -0.5f, 1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.0f, -0.5f, -1.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.0f, -0.5f, -2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-3.0f, -0.5f, -3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.0f, -0.5f, -2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.0f, -0.5f, -3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-4.5f, -0.5f, -4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.5f, -0.5f, -4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.0f, -0.5f, -3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-2.0f, -0.5f, -2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.5f, -0.5f, -2.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-0.5f, -0.5f, -2.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(0.5f, -0.5f, -2.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.0f, -0.5f, -2.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(1.0f, -0.5f, -3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-1.0f, -0.5f, -3.5f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(0.5f, -0.5f, -4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.1f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-0.5f, -0.5f, -4.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);

    wall = new Wall();
    wall->setPosition(glm::vec3(-0.5f, -0.5f, -3.0f));
    wall->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    gameElements.push_back(wall);
}