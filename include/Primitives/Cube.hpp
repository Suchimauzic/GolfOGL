#ifndef CUBE_HPP
#define CUBE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

#include "Primitives/Object.hpp"

#include <vector>

class Cube : public Object
{
public:
    Cube();
    ~Cube();

private:
    void generate() override;
};

#endif