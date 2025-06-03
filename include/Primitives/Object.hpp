#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Core/Shader.hpp"

#include "Components/Mesh.hpp"
#include "Components/Vertex.hpp"
#include "Components/Texture.hpp"

#include "Manager/TextureManager.hpp"
#include "Manager/ShaderManager.hpp"

#include "Camera.hpp"

#include <vector>
#include <string>

class Object
{
public:
    virtual ~Object();

    virtual void render(Camera* camera, int width, int height);

    void loadTexture(const std::string& textureName);
    void loadShader(const std::string& shaderName);

    // Setters
    void setPosition(const glm::vec3 position);
    void setSize(const glm::vec3 size);
    void setRotation(const float angle, const glm::vec3 rotation);
    void setColor(const std::string& colorName, const glm::vec3& color);

    // Getters
    glm::vec3 getPosition();
    glm::vec3 getGlobalPosition();
    glm::vec3 getSize() const;
    glm::vec3 getRotation() const;
    std::string getShader() const;
    Mesh* getMesh();
    glm::mat4 getModel() const;
    std::vector<glm::vec3> getWorldVertices() const;
    std::vector<glm::vec3> getWorldVertices(const glm::vec3& position) const;

protected:
    Mesh* mesh;
    
    unsigned int VAO, VBO, EBO;

    std::string shaderName;
    std::string textureName;

    // Matrices
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    // Properties
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;
    float angle;

    Object();

    virtual void generate() = 0;
};

#endif