#include "GameElements/DeadEndElement.hpp"

DeadEndElement::DeadEndElement()
    : GameElement()
{}

void DeadEndElement::generate()
{
    // Left wall
    Cube* wall = new Cube();
    wall->setPosition(position);
    wall->setRotation(rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    objects.push_back(wall);


    // Bottom wall
    glm::vec3 wallDistance = glm::vec3(0.5f, 0.0f, -0.45f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 globalOffset = rotationMatrix * glm::vec4(wallDistance, 1.0f);
    
    wall = new Cube();
    wall->setPosition(position + globalOffset);
    wall->setRotation(90.0f + rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 0.9f));
    objects.push_back(wall);


    // Right wall
    wallDistance = glm::vec3(1.0f, 0.0f, 0.0f);
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    globalOffset = rotationMatrix * glm::vec4(wallDistance, 1.0f);
    
    wall = new Cube();
    wall->setPosition(position + globalOffset);
    wall->setRotation(rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    wall->setSize(glm::vec3(0.1f, 1.0f, 1.0f));
    objects.push_back(wall);
}