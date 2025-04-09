#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"

#include <vector>
#include <cmath>

class Sphere
{
public:
    Sphere(float radius, int sectorCount, int stackCount);
    ~Sphere();

    void render(Shader shader, int width, int height);
    void setPosition(const glm::vec3 position);
    void setSize(const glm::vec3 size);
    void setRotate(const float angle, const glm::vec3 rotate);

private:
    std::vector<float> vertices;
    std::vector<int> indices;
    unsigned int VAO, VBO;
    unsigned int EBO;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    void generate(float radius, int sectorCount, int stackCount);
};

#endif