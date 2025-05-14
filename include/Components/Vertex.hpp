#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texture;

    Vertex() = default;
    
    Vertex
    (
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2 texture = glm::vec2(0.0f, 0.0f)
    )
        : position(position),
          texture(texture)
    {}
};

#endif