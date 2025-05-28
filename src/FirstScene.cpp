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
}