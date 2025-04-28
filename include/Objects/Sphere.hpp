#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"

#include "Objects/Object.hpp"

#include <vector>
#include <cmath>

class Sphere : public Object
{
public:
    Sphere(float radius, int sectorCount, int stackCount);
    ~Sphere();

    void render(Camera* camera, Shader* shader, int width, int height) override;

private:
    std::vector<int> indices;
    unsigned int EBO;

    float radius;
    int sectorCount;
    int stackCount;

    void generate() override;
};

#endif