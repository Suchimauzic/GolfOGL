#include "Objects/Sphere.hpp"

Sphere::Sphere(float radius, int sectorCount, int stackCount) : model(glm::mat4(1.0f))
{
    generate(radius, sectorCount, stackCount);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Sphere::~Sphere()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}

void Sphere::render(Shader shader, int width, int height)
{
    shader.use();
    projection = glm::perspective(glm::radians(Window::camera->zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    view = Window::camera->getViewMatrix();
    shader.setMat4("view", view);

    glBindVertexArray(VAO);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setMat4("model", model);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::setPosition(const glm::vec3 position)
{
    model = glm::translate(model, position);
}

void Sphere::setSize(const glm::vec3 size)
{
    model = glm::scale(model, size);
}

void Sphere::setRotate(const float angle, const glm::vec3 rotate)
{
    model = glm::rotate(model, glm::radians(angle), rotate);
}

void Sphere::generate(float radius, int sectorCount, int stackCount)
{
    vertices.clear();
    indices.clear();

    float x
    float y;
    float z;
    float xy;
    
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
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            for (int k = 0; k < 3; ++k)
                vertices.push_back(i / (sectorCount / 2));
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
}