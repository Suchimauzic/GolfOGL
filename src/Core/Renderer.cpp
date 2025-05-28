#include "Core/Renderer.hpp"

std::vector<Object*> Renderer::objectsRender = {};

void Renderer::addObject(Object& object)
{
    objectsRender.push_back(&object);
}

void Renderer::addObjects(std::vector<Object*> objects)
{
    for (Object* object : objects)
    {
        objectsRender.push_back(&*object);
    }
}

void Renderer::removeObject(Object& object)
{
    for (int i = 0; i < objectsRender.size(); ++i)
    {
        if (objectsRender[i] == &object)
        {
            objectsRender.erase(objectsRender.begin() + i);
        }
    }
}

void Renderer::draw(Camera* camera)
{
    for (Object* object : objectsRender)
    {
        object->render(camera, GameConfig::width, GameConfig::height);
    }
}