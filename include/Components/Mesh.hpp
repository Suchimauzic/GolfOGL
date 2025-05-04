#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Components/Vertex.hpp"

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices);
    ~Mesh() = default;

    std::vector<Vertex> getVertices() const;
    std::vector<int> getIndices() const;

private:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
};

#endif