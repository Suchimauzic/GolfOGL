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

    for (int i = 0; i < 100; ++i)
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

    return false;
}

bool Collider::isCollision
(
    const std::vector<glm::vec3>& verticesA,
    const std::vector<glm::vec3>& verticesB,
    glm::vec3& normal,
    float& penetrationDepth
)
{
    // First support point
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 support = supportVertex(verticesA, verticesB, direction);

    Simplex simplex;
    // First simplex point
    simplex.push_front(support);

    // Direction is towards to origin
    direction = -support;

    for (int i = 0; i < 100; ++i)
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

    return false;
}


bool Collider::EPA
(
    const Simplex& simplex,
    const std::vector<glm::vec3>& verticesA,
    const std::vector<glm::vec3>& verticesB,
    glm::vec3& normal,
    float& penetrationDepth
)
{
    std::vector<glm::vec3> polytope(simplex.begin(), simplex.end());
    std::vector<int> faces =
    {
        0, 1, 2,
        0, 3, 1,
        0, 2, 3,
        1, 3, 2
    };

    std::vector<glm::vec4> normals;
    int minFace;
    getFaceNormals(polytope, faces, normals, minFace);

    glm::vec3 minNormal;
    float minDistance = FLT_MAX;

    while (minDistance == FLT_MAX)
    {
        minNormal = glm::vec3(normals[minFace].x, normals[minFace].y, normals[minFace].z);
        minDistance = normals[minFace].w;

        glm::vec3 support = supportVertex(verticesA, verticesB, minNormal);
        float sDistance = glm::dot(minNormal, support);

        if (glm::abs(sDistance - minDistance) > 0.001f)
        {
            minDistance = FLT_MAX;
            std::vector<std::pair<int, int>> uniqueEdges;

            for (int i = 0; i < normals.size(); ++i)
            {
                if (sameDirection(normals[i], support))
                {
                    int f = i * 3;

                    addIfUniqueEdge(uniqueEdges, faces, f, f + 1);
                    addIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
                    addIfUniqueEdge(uniqueEdges, faces, f + 2, f);

                    faces[f + 2] = faces.back();
                    faces.pop_back();

                    faces[f + 1] = faces.back();
                    faces.pop_back();

                    faces[f] = faces.back();
                    faces.pop_back();

                    normals[i] = normals.back();
                    normals.pop_back();

                    --i;
                }
            }

            std::vector<int> newFaces;

            for (auto [edgeIndex1, edgeIndex2] : uniqueEdges)
            {
                newFaces.push_back(edgeIndex1);
                newFaces.push_back(edgeIndex2);
                newFaces.push_back(polytope.size());
            }

            polytope.push_back(support);

            std::vector<glm::vec4> newNormals;
            int newMinFace;
            getFaceNormals(polytope, newFaces, newNormals, newMinFace);

            float oldMinDistance = FLT_MAX;
            
            for (int i = 0; i < normals.size(); ++i)
            {
                if (normals[i].w < oldMinDistance)
                {
                    oldMinDistance = normals[i].w;
                    minFace = i;
                }
            }

            if (newNormals[newMinFace].w < oldMinDistance)
            {
                minFace = newMinFace + normals.size();
            }

            faces.insert(faces.end(), newFaces.begin(), newFaces.end());
            normals.insert(normals.end(), newNormals.begin(), newNormals.end());
        }
    }

    normal = minNormal;
    penetrationDepth = minDistance + 0.001f;

    return true;
}


// For GJK

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

// For EPA

void Collider::getFaceNormals
(
    const std::vector<glm::vec3>& polytope,
    const std::vector<int>& faces,
    std::vector<glm::vec4> normalsOut,
    int minFaceOut
)
{
    std::vector<glm::vec4> normals;
    int minTriangle = 0;
    float minDistance = FLT_MAX;

    for (int i = 0; i < faces.size(); i += 3)
    {
        glm::vec3 a = polytope[faces[i]];
        glm::vec3 b = polytope[faces[i + 1]];
        glm::vec3 c = polytope[faces[i + 2]];

        glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        float distance = glm::dot(normal, a);

        if (distance < 0)
        {
            normal *= -1;
            distance *= -1;
        }

        normals.emplace_back(normal, distance);

        if (distance < minDistance)
        {
            minTriangle = i / 3;
            minDistance = distance;
        }
    }

    normalsOut = normals;
    minFaceOut = minTriangle;
}

void Collider::addIfUniqueEdge
(
    std::vector<std::pair<int, int>>& edges,
    const std::vector<int>& faces,
    int a,
    int b
)
{
    auto reverse = std::find
    (
        edges.begin(),
        edges.end(),
        std::make_pair(faces[b], faces[a])
    );

    if (reverse != edges.end())
    {
        edges.erase(reverse);
    }
    else
    {
        edges.emplace_back(faces[a], faces[b]);
    }
}