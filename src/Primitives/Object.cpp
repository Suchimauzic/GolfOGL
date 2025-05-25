#include "Primitives/Object.hpp"

Object::Object()
    : model(glm::mat4(1.0f)),
    textureName("")
{}

Object::~Object()
{
    delete mesh;
}

void Object::render(Camera* camera, int width, int height)
{
    // glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture2D(textureName).getId());

    Shader* shader = &ShaderManager::getShader(shaderName);
    shader->use();
    projection = glm::perspective(glm::radians(camera->getZoom()), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    shader->setMat4("projection", projection);

    view = camera->getViewMatrix();
    shader->setMat4("view", view);

    glBindVertexArray(VAO);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shader->setMat4("model", model);

    glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
}

void Object::loadTexture(const std::string& textureName)
{
    this->textureName = textureName;
}

void Object::loadShader(const std::string& shaderName)
{
    this->shaderName = shaderName;
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

glm::vec3 Object::getPosition() const
{
    return position;
}

glm::vec3 Object::getSize() const
{
    return size;
}

glm::vec3 Object::getRotation() const
{
    return rotation;
}

std::string Object::getShader() const
{
    return shaderName;
}

Mesh* Object::getMesh()
{
    return mesh;
}

glm::mat4 Object::getModel() const
{
    return model;
}

std::vector<glm::vec3> Object::getWorldVertices() const
{
    std::vector<glm::vec3> worldVertices;
    std::vector<Vertex> meshVertices = mesh->getVertices();

    for (int i = 0; i < meshVertices.size(); ++i)
    {
        worldVertices.push_back(glm::vec3
        (
            this->getModel() * glm::vec4(meshVertices[i].position, 1.0f)
        ));
    }

    return worldVertices;
}