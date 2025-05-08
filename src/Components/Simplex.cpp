#include "Components/Simplex.hpp"

Simplex::Simplex()
    : size(0),
    vertices
    (
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f)
        }
    )
{}

Simplex& Simplex::operator=(std::array<glm::vec3, 4> array)
{
    for (unsigned int point = 0; point < array.size(); ++point)
        vertices[point] = array[point];

    size = array.size();
    return *this;
}

void Simplex::push_front(glm::vec3 vertex)
{
    vertices = { vertex, vertices[0], vertices[1], vertices[2] };
    size = std::min(size + 1, 4u);
}

glm::vec3& Simplex::operator[](unsigned int i)
{
    return vertices[i];
}

unsigned int Simplex::getSize() const
{
    return size;
}