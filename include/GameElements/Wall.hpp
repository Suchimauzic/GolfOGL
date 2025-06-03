#ifndef WALL_HPP
#define WALL_HPP

#include <glm/glm.hpp>
#include "Primitives/Cube.hpp"
#include "GameElements/CollisionState.hpp"
#include "GameElements/GameElement.hpp"

class Wall : public GameElement
{
public:
    Wall();
    ~Wall();

    void loadShader(const std::string& shaderName) override;

    // Setters
    void setPosition      (glm::vec3 position)              override;
    void setRotation      (float angle, glm::vec3 rotation) override;
    void setSize          (glm::vec3 size)                  override;
    void setCollisionState(CollisionState collisionState)   override;

    // Getters
    glm::vec3      getPosition()       const override;
    glm::vec3      getGlobalPosition() const override;
    glm::vec3      getRotation()       const override;
    glm::vec3      getSize()           const override;
    CollisionState getCollisionState() const override;
    Object&        getObject()               override;

private:
    Cube* cube;
};

#endif