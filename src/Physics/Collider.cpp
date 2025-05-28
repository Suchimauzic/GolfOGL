#include "Physics/Collider.hpp"

bool Collider::isCollision(const std::vector<glm::vec3>& verticesA, const std::vector<glm::vec3>& verticesB)
{
    // First support point
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 support = supportVertex(verticesA, verticesB, direction);

    Simplex simplex;
    // First simplex point
    simplex.push_front(support);

    // Direction is towards to origin
    direction = -support;

    while (true)
    {
        // New support point
        support = supportVertex(verticesA, verticesB, direction);

        if (glm::dot(support, direction) <= 0)
        {
            return false;
        }
        
        simplex.push_front(support);

        // Check collision
        if (nextSimplex(simplex, direction))
        {
            return true;
        }
    }
}

glm::vec3 Collider::findFurthestVertex(const std::vector<glm::vec3>& vertices, const glm::vec3& direction)
{
    glm::vec3 maxVertex;
    float maxDistance = -FLT_MAX;

    // Recieve furthest vertex
    for (glm::vec3 vertex : vertices)
    {
        float distance = glm::dot(vertex, direction);

        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxVertex = vertex;
        }
    }

    return maxVertex;
}

glm::vec3 Collider::supportVertex
(
    const std::vector<glm::vec3>& verticesA,
    const std::vector<glm::vec3>& verticesB,
    const glm::vec3& direction)
{
    glm::vec3 furthestVertexA = findFurthestVertex(verticesA, direction);
    glm::vec3 furthestVertexB = findFurthestVertex(verticesB, -direction);

    // Minkowski difference
    return furthestVertexA - furthestVertexB;
}

bool Collider::nextSimplex(Simplex& simplex, glm::vec3& direction)
{
    switch (simplex.getSize())
    {
        case 2:
            return lineSimplex(simplex, direction);
        case 3:
            return triangleSimplex(simplex, direction);
        case 4:
            return tetrahedronSimplex(simplex, direction);
        default:
            return false;
    }
}

bool Collider::sameDirection(const glm::vec3& direction, const glm::vec3& ao)
{
    return glm::dot(direction, ao) > 0;
}

bool Collider::lineSimplex(Simplex& simplex, glm::vec3& direction)
{
    glm::vec3 a = simplex[0];
    glm::vec3 b = simplex[1];

    glm::vec3 ab = b - a;
    glm::vec3 ao = -a;

    if (sameDirection(ab, ao))
    {
        direction = glm::cross(glm::cross(ab, ao), ab);
    }
    else
    {
        simplex = { a };
        direction = ao;
    }

    return false;
}

bool Collider::triangleSimplex(Simplex& simplex, glm::vec3& direction)
{
    glm::vec3 a = simplex[0];
    glm::vec3 b = simplex[1];
    glm::vec3 c = simplex[2];

    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ao = -a;

    glm::vec3 abc = glm::cross(ab, ac);

    if (sameDirection(glm::cross(abc, ac), ao))
    {
        if (sameDirection(ac, ao))
        {
            simplex = { a, c };
            direction = glm::cross(glm::cross(ac, ao), ac);
        }
        else
        {
            return lineSimplex(simplex = { a, b }, direction);
        }
    }
    else
    {
        if (sameDirection(glm::cross(ab, abc), ao))
        {
            return lineSimplex(simplex = { a, b }, direction);
        }
        else
        {
            if (sameDirection(abc, ao))
            {
                direction = abc;
            }
            else
            {
                simplex = { a, b, c };
                direction = -abc;
            }
        }
    }

    return false;
}

bool Collider::tetrahedronSimplex(Simplex& simplex, glm::vec3& direction)
{
    glm::vec3 a = simplex[0];
    glm::vec3 b = simplex[1];
    glm::vec3 c = simplex[2];
    glm::vec3 d = simplex[3];

    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ad = d - a;
    glm::vec3 ao = -a;

    glm::vec3 abc = glm::cross(ab, ac);
    glm::vec3 acd = glm::cross(ac, ad);
    glm::vec3 adb = glm::cross(ad, ab);

    if (sameDirection(abc, ao))
    {
        return triangleSimplex(simplex = { a, b, c }, direction);
    }

    if (sameDirection(acd, ao))
    {
        return triangleSimplex(simplex = { a, c, d }, direction);
    }

    if (sameDirection(adb, ao))
    {
        return triangleSimplex(simplex = { a, d, b }, direction);
    }

    return true;
}