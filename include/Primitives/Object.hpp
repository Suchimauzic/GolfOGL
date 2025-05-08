#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

#include "Components/Mesh.hpp"
#include "Components/Vertex.hpp"

#include <vector>

class Object
{
public:
    virtual void render(Camera* camera, Shader* shader, int width, int height);

    // Setters
    void setPosition(const glm::vec3 position);
    void setSize(const glm::vec3 size);
    void setRotation(const float angle, const glm::vec3 rotation);

    // Getters
    glm::vec3 getPosition();
    glm::vec3 getSize();
    glm::vec3 getRotation();
    Mesh* getMesh()
    {
        return mesh;
    }

    glm::mat4 getModelMatrix()
    {
        return model;
    }

    std::vector<glm::vec3> getWorldVertices()
    {
        std::vector<glm::vec3> worldVertices;
        std::vector<Vertex> meshVertices = mesh->getVertices();

        for (int i = 0; i < meshVertices.size(); ++i)
        {
            worldVertices.push_back(glm::vec3
            (
                this->getModelMatrix() * glm::vec4(meshVertices[i].position, 1.0f)
            ));
        }

        return worldVertices;
    }

protected:
    Mesh* mesh;
    
    unsigned int VAO, VBO, EBO;

    // Matrices
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    // Properties
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;

    Object();
    virtual ~Object();

    virtual void generate();
};

#endif