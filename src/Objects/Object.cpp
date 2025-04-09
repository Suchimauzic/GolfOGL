#include "Objects/Object.hpp"

Object::Object(int width, int height)
    : model(glm::mat4(1.0f)),
    view(Window::camera->getViewMatrix()),
    projection(
        glm::perspective(
            glm::radians(Window::camera->zoom),
            static_cast<float>(width) / static_cast<float>(height),
            0.1f,
            100.0f
        )
    )
{
}

void Object::render(Shader shader, int width, int height)
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