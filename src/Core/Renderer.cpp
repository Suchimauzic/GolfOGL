#include "Core/Renderer.hpp"

void Renderer::addObject(Object& object)
{
    objects.push_back(&object);
}

void Renderer::removeObject(Object& object)
{
    for (int i = 0; i < objects.size(); ++i)
    {
        if (objects[i] == &object)
        {
            objects.erase(objects.begin() + i);
        }
    }
}

void Renderer::draw(Camera* camera)
{
    for (Object* object : objects)
    {
        object->render(camera, GameConfig::width, GameConfig::height);
    }
}