#ifndef GAMEELEMENT_HPP
#define GAMEELEMENT_HPP

#include <string>

#include <glm/glm.hpp>
#include "Primitives/Object.hpp"
#include "GameElements/CollisionState.hpp"

class GameElement
{
public:
    virtual ~GameElement() = default;

    virtual void loadShader(const std::string& shaderName) = 0;

    // Setters
    virtual void setPosition      (glm::vec3 position)              = 0;
    virtual void setRotation      (float angle, glm::vec3 rotation) = 0;
    virtual void setSize          (glm::vec3 size)                  = 0;
    virtual void setCollisionState(CollisionState collisionState)   = 0;

    // Getters
    virtual glm::vec3      getPosition()       const = 0;
    virtual glm::vec3      getGlobalPosition() const = 0;
    virtual glm::vec3      getRotation()       const = 0;
    virtual glm::vec3      getSize()           const = 0;
    virtual CollisionState getCollisionState() const = 0;
    virtual Object&        getObject()               = 0;

protected:
    CollisionState collisionState = CollisionState::NONE;

    GameElement() = default;
    GameElement(CollisionState collisionState);
};

#endif