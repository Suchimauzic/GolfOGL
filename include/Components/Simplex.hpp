#ifndef SIMPLEX_HPP
#define SIMPLEX_HPP

#include <glm/glm.hpp>

#include "Components/Vertex.hpp"

class Simplex
{
public:
    Simplex();
    
    Simplex& operator=(std::array<glm::vec3, 4> array);
    glm::vec3& operator[](unsigned int i);

    void push_front(glm::vec3 vertex);
    unsigned int getSize() const;

private:
    std::array<glm::vec3, 4> vertices;
    unsigned int size;
};

#endif