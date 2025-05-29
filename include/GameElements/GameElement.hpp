#ifndef GAMEELEMENT_HPP
#define GAMEELEMENT_HPP

#include "Primitives/Cube.hpp"
#include "Core/Renderer.hpp"
#include <vector>

class GameElement
{
public:
    virtual ~GameElement();

    virtual void generate() = 0;

    void loadShader(const std::string& shaderName);
    void loadRenderer();

    void setPosition(glm::vec3 position);
    void setRotation(float rotation);

protected:
    std::vector<Object*> objects;
        
    glm::vec3 position;
    float rotation;
    
    GameElement();
};

#endif