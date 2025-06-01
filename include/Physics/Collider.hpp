#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>

#include <cmath>
#include <algorithm>

#include "Components/Vertex.hpp"
#include "Components/Mesh.hpp"
#include "Physics/Simplex.hpp"

/*
======================================
    The program uses GJK algorithm
    to detect a collision
======================================
*/

class Collider
{
public:
    bool isCollision(const std::vector<glm::vec3>& verticesA, const std::vector<glm::vec3>& verticesB);

    bool isCollision
    (
        const std::vector<glm::vec3>& verticesA,
        const std::vector<glm::vec3>& verticesB,
        glm::vec3& normal,
        float& penetrationDepth
    );

private:
    glm::vec3 findFurthestVertex(const std::vector<glm::vec3>& vertices, const glm::vec3& direction);

    glm::vec3 supportVertex
    (
        const std::vector<glm::vec3>& verticesA,
        const std::vector<glm::vec3>& verticesB,
        const glm::vec3& direction
    );

    // For GJK
    bool nextSimplex(Simplex& simplex, glm::vec3& direction);
    bool sameDirection(const glm::vec3& direction, const glm::vec3& ao);
    bool lineSimplex(Simplex& simplex, glm::vec3& direction);
    bool triangleSimplex(Simplex& simplex, glm::vec3& direction);
    bool tetrahedronSimplex(Simplex& simplex, glm::vec3& direction);

    // For EPA
    bool EPA
    (
        const Simplex& simplex,
        const std::vector<glm::vec3>& verticesA,
        const std::vector<glm::vec3>& verticesB,
        glm::vec3& normal,
        float& penetrationDepth
    );
    
    void getFaceNormals
    (
        const std::vector<glm::vec3>& polytop,
        const std::vector<int>& faces,
        std::vector<glm::vec4> normalsOut,
        int minFaceOut
    );

    void addIfUniqueEdge
    (
        std::vector<std::pair<int, int>>& edges,
        const std::vector<int>& faces,
        int a,
        int b
    );
};

#endif