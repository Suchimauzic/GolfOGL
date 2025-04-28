#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"

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

protected:
    std::vector<float> vertices;
    unsigned int VAO, VBO;

    // Matrices
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    // Properties
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;

    Object();
    virtual ~Object() = default;

    virtual void generate();
};

#endif