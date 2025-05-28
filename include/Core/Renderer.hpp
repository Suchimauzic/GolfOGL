#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GameConfig.hpp"

#include "Primitives/Object.hpp"
#include "Primitives/Cube.hpp"
#include "Primitives/Sphere.hpp"

#include <vector>

class Renderer
{
public:
    // Renderer() = default;
    // ~Renderer() = default;

    static void addObject(Object& object);
    static void addObjects(std::vector<Object*> objects);
    static void removeObject(Object& object);

    static void draw(Camera* camera);

private:
    static std::vector<Object*> objectsRender;
};

#endif