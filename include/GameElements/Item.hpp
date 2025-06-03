#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include <glm/glm.hpp>
#include "Primitives/Sphere.hpp"
#include "GameElements/CollisionState.hpp"
#include "GameElements/GameElement.hpp"

class Item : public GameElement
{
public:
    Item();
    ~Item();

    void loadShader(const std::string& shaderName) override;

    // Setters
    void setPosition      (glm::vec3 position)              override;
    void setRotation      (float angle, glm::vec3 rotation) override;
    void setSize          (glm::vec3 size)                  override;
    void setCollisionState(CollisionState collisionState)   override;
    void setColor         (const std::string& colorName, const glm::vec3& color);

    // Getters
    glm::vec3      getPosition()       const override;
    glm::vec3      getGlobalPosition() const override;
    glm::vec3      getRotation()       const override;
    glm::vec3      getSize()           const override;
    CollisionState getCollisionState() const override;
    Object&        getObject()               override;

private:
    Sphere* sphere;
};

#endif