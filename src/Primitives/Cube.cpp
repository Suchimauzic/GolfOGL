#include "Primitives/Cube.hpp"

Cube::Cube() : Object()
{
    generate();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(Vertex), mesh->getVertices().data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(int), mesh->getIndices().data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}

void Cube::generate()
{
    // std::vector<Vertex> vertices =
    // {
    //     // vertex            color
    //     // front
    //     -0.5f,  0.5f,  0.5f,  0.25f,  0.4f,  0.6f,      // top left
    //     -0.5f, -0.5f,  0.5f,  0.34f, 0.62f,  0.3f,      // bottom left
    //      0.5f, -0.5f,  0.5f,  0.54f,  0.1f, 0.92f,      // bottom right
    //      0.5f,  0.5f,  0.5f,  0.41f, 0.32f, 0.24f,      // top right

    //     // back
    //     -0.5f,  0.5f, -0.5f,  0.54f,  0.1f, 0.92f,      // top left
    //     -0.5f, -0.5f, -0.5f,  0.34f, 0.62f,  0.3f,      // bottom left
    //      0.5f, -0.5f, -0.5f,  0.25f,  0.4f,  0.6f,      // bottom right
    //      0.5f,  0.5f, -0.5f,  0.41f, 0.32f, 0.24f       // top right
    // };

    std::vector<Vertex> vertices;

    // Front

    // Vertex 1 (Top left)
    Vertex vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f));
    vertices.push_back(vertex);

    // Vertex 2 (Bottom left)
    vertex.position = glm::vec3(-0.5f, -0.5f, 0.5f);
    vertex.texture = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    
    // Vertex 3 (Bottom right)
    vertex.position = glm::vec3(0.5f, -0.5f, 0.5f);
    vertex.texture = glm::vec2(1.0f, 0.0f);
    vertices.push_back(vertex);

    // Vertex 4 (Top right)
    vertex.position = glm::vec3(0.5f, 0.5f, 0.5f);
    vertex.texture = glm::vec2(1.0f, 1.0f);
    vertices.push_back(vertex);

    // Back

    // Vertex 5 (Top left)
    vertex.position = glm::vec3(-0.5f, 0.5f, -0.5f);
    vertex.texture = glm::vec2(0.0f, 1.0f);
    vertices.push_back(vertex);

    // Vertex 6 (Bottom left)
    vertex.position = glm::vec3(-0.5f, -0.5f, -0.5f);
    vertex.texture = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);

    // Vertex 7 (Bottom right)
    vertex.position = glm::vec3(0.5f, -0.5f, -0.5f);
    vertex.texture = glm::vec2(1.0f, 0.0f);
    vertices.push_back(vertex);

    // Vertex 8 (Top right)
    vertex.position = glm::vec3(0.5f, 0.5f, -0.5f);
    vertex.texture = glm::vec2(1.0f, 1.0f);
    vertices.push_back(vertex);

    std::vector<int> indices = 
    {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Left
        4, 5, 1,
        4, 1, 0,

        // Right
        3, 2, 6,
        3, 6, 7,

        // Back
        7, 6, 5,
        7, 5, 4,

        // Upper
        4, 0, 3,
        4, 3, 7,

        // Lower
        1, 5, 6,
        1, 6, 2
    };

    mesh = new Mesh(vertices, indices);
}