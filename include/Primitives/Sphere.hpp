#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Core/Shader.hpp"

#include "Primitives/Object.hpp"

#include "Camera.hpp"

#include <vector>
#include <cmath>

class Sphere : public Object
{
public:
    Sphere(float radius, int sectorCount, int stackCount);
    ~Sphere();

private:
    float radius;
    int sectorCount;
    int stackCount;

    void generate() override;
};

#endif