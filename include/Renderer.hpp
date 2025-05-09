#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GameConfig.hpp"

#include "Primitives/Object.hpp"
#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"

#include "vector"

class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

    void addObject(Object& object);
    void removeObject(Object& object);

    void draw(Camera* camera, Shader* shader);

private:
    std::vector<Object*> objects;
};

#endif