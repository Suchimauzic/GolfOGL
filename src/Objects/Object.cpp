#include "Objects/Object.hpp"

Object::Object() : model(glm::mat4(1.0f))
{
}

void Object::render(Camera* camera, Shader* shader, int width, int height)
{
    shader->use();
    projection = glm::perspective(glm::radians(camera->zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    view = camera->getViewMatrix();
    shader->setMat4("view", view);

    glBindVertexArray(VAO);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shader->setMat4("model", model);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Object::setPosition(const glm::vec3 position)
{
    this->position = position;
    model = glm::translate(model, position);
}

void Object::setSize(const glm::vec3 size)
{
    this->size = size;
    model = glm::scale(model, size);
}

void Object::setRotation(const float angle, const glm::vec3 rotation)
{
    this->rotation = rotation;
    model = glm::rotate(model, glm::radians(angle), rotation);
}

glm::vec3 Object::getPosition()
{
    return position;
}

glm::vec3 Object::getSize()
{
    return size;
}

glm::vec3 Object::getRotation()
{
    return rotation;
}

void Object::generate()
{
}