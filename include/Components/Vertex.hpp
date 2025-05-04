#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;

    Vertex() = default;
    Vertex(glm::vec3 position) : position(position)
    {}
};

#endif