#ifndef SIMPLEX_HPP
#define SIMPLEX_HPP

#include <glm/glm.hpp>

#include "Components/Vertex.hpp"

class Simplex
{
public:
    Simplex();
    
    Simplex& operator=(std::vector<glm::vec3> points);
    glm::vec3& operator[](unsigned int i);

    void push_front(glm::vec3 vertex);
    unsigned int getSize() const;
    std::array<glm::vec3, 4> getVertices();

    auto begin() const { return vertices.begin(); }
    auto end() const { return vertices.end() - (4 - size); }

private:
    std::array<glm::vec3, 4> vertices;
    unsigned int size;
};

#endif