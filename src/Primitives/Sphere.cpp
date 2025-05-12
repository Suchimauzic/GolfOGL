#include "Primitives/Sphere.hpp"

Sphere::Sphere(float radius, int sectorCount, int stackCount)
    : Object(), radius(radius), sectorCount(sectorCount), stackCount(stackCount) 
{
    generate();

    texture = new Texture("res/Textures/GolfBallTexture.jpg");

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(Vertex), mesh->getVertices().data(), GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(float), mesh->getIndices().data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
    glEnableVertexAttribArray(2);

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

    float xPos, yPos, zPos, xyPos;  // position
    float xTexture, yTexture;
    
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngel, stackAngle;

    int k1, k2;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;
        xyPos = radius * cosf(stackAngle);
        zPos = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngel = j * sectorStep;

            xPos = xyPos * cosf(sectorAngel);
            yPos = xyPos * sinf(sectorAngel);


            // Texture coords

            float absX = fabs(xPos);
            float absY = fabs(yPos);
            float absZ = fabs(zPos);

            if (absX >= absY && absX >= absZ)
            {
                float invAbsX = 1.0f / absX;
                if (xPos > 0)
                {
                    xTexture = zPos;
                }
                else
                {
                    xTexture = -zPos;
                }

                xTexture /= absX;
                yTexture = yPos / absX;
            }
            else if (absY >= absZ)
            {
                xTexture = xPos / absY;

                if (yPos > 0)
                {
                    yTexture = zPos;
                }
                else
                {
                    yTexture = -zPos;
                }

                yTexture /= absY;
            }
            else
            {
                xTexture = xPos / absZ;
                yTexture = yPos / absZ;
            }

            xTexture = 0.5f * (xTexture + 1.0f);
            yTexture = 0.5f * (yTexture + 1.0f);

            Vertex vertex
            (
                glm::vec3(xPos, yPos, zPos),
                glm::vec3(1.0f, 0.5f, 0.0f),
                glm::vec2(xTexture, yTexture)
            );

            vertices.push_back(vertex);
        }
    }    

    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
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