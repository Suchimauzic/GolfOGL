#include "Components/Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices)
    : vertices(vertices),
      indices(indices)
{}

std::vector<Vertex> Mesh::getVertices() const
{
    return vertices;
}

std::vector<int> Mesh::getIndices() const
{
    return indices;
}