#include "FirstScene.hpp"

#include "GameElements/TurnElement.hpp"

FirstScene::FirstScene()
{
    generateLevel();
    loadShader();
    loadRenderer();
}

FirstScene::~FirstScene()
{
    for (Object* object : levelObjects)
    {
        Renderer::removeObject(*object);
        delete object; 
    }
}

void FirstScene::loadShader()
{
    for (Object* object : levelObjects)
    {
        object->loadShader("CubeShader");
    }
}

void FirstScene::loadRenderer()
{
    for (Object* object : levelObjects)
    {
        Renderer::addObject(*object);
    }
}

void FirstScene::generateLevel()
{
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
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);

    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, 3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);
    
    cube = new Cube();
    cube->setPosition(glm::vec3(4.0f, -0.5f, 3.5f));
    cube->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    levelObjects.push_back(cube);
}