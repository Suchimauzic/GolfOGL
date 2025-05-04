#include "Primitives/Sphere.hpp"

Sphere::Sphere(float radius, int sectorCount, int stackCount)
    : Object(), radius(radius), sectorCount(sectorCount), stackCount(stackCount) 
{
    generate();

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(Vertex), mesh->getVertices().data(), GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(float), mesh->getIndices().data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Sphere::~Sphere()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}

void Sphere::generate()
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    vertices.clear();
    indices.clear();

    float x, y, z, xy;
    
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngel, stackAngle;

    int k1, k2;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngel = j * sectorStep;

            x = xy * cosf(sectorAngel);
            y = xy * sinf(sectorAngel);

            Vertex vertex(glm::vec3(x, y, z));
            vertices.push_back(vertex);

            // for (int k = 0; k < 3; ++k)
            //     vertices.push_back(i / (sectorCount / 2));
        }
    }    

    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i* (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    mesh = new Mesh(vertices, indices);
}