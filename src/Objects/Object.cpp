#include "Objects/Object.hpp"

Object::Object() : model(glm::mat4(1.0f))
{
}

Object::~Object()
{
}

void Object::render(Camera* camera, Shader shader, int width, int height)
{
}

void Object::setPosition(const glm::vec3 position)
{
    model = glm::translate(model, position);
}

void Object::setSize(const glm::vec3 size)
{
    model = glm::scale(model, size);
}

void Object::setRotate(const float angle, const glm::vec3 rotate)
{
    model = glm::rotate(model, glm::radians(angle), rotate);
}

void Object::generate()
{
}