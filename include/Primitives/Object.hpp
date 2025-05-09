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
    glm::vec3 getPosition() const;
    glm::vec3 getSize() const;
    glm::vec3 getRotation() const;
    Mesh* getMesh();
    glm::mat4 getModel() const;
    std::vector<glm::vec3> getWorldVertices() const;

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