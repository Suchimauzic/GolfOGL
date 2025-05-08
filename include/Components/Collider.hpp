#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>

#include "Components/Vertex.hpp"
#include "Components/Mesh.hpp"
#include "Components/Simplex.hpp"

/*
======================================
    The program uses GJK algorithm
    to find a collision
======================================
*/

class Collider
{
public:
    bool isCollision(const std::vector<glm::vec3>& pointA, const std::vector<glm::vec3>& pointB);
    glm::vec3 findFurthestPoint(const std::vector<glm::vec3>& vertices, const glm::vec3& direction);

    glm::vec3 supportPoint
    (
        const std::vector<glm::vec3>& pointA,
        const std::vector<glm::vec3>& pointB,
        const glm::vec3 direction
    );

    bool nextSimplex(Simplex& simplex, glm::vec3& direction);
    bool sameDirection(const glm::vec3& direction, const glm::vec3& ao);
    bool lineSimplex(Simplex& simplex, glm::vec3& direction);
    bool triangleSimplex(Simplex& simplex, glm::vec3& direction);
    bool tetrahedronSimplex(Simplex& simplex, glm::vec3& direction);
};

#endif