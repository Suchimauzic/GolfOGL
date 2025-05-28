#ifndef DEADEND_HPP
#define DEADEND_HPP

#include "GameElements/GameElement.hpp"
#include "Primitives/Cube.hpp"
#include "Core/Renderer.hpp"
#include <vector>

class DeadEndElement : public GameElement
{
public:
    DeadEndElement();
    ~DeadEndElement() = default;

    void generate() override;
};

#endif