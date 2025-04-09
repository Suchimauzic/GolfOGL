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

    Object(int width, int height);
    virtual ~Object();

    virtual void render(Shader shader, int width, int height);
    void setPosition(const glm::vec3 position);
    void setSize(const glm::vec3 size);
    void setRotate(const float angle, const glm::vec3 rotate);

protected:
    std::vector<float> vertices;
    unsigned int VAO, VBO;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    virtual void generate();
};

#endif