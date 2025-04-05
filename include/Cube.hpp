#ifndef CUBE_HPP
#define CUBE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"

#include <vector>

class Cube
{
public:
    Cube();
    ~Cube();

    void render(Shader shader, int width, int height);
    void setPosition(const glm::vec3 position);
    void setSize(const glm::vec3 size);
    void setRotate(const float angle, const glm::vec3 rotate);

private:
    std::vector<float> vertices;
    unsigned int VAO, VBO;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

#endif