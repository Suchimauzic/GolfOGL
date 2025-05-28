#ifndef TURNELEMENT_HPP
#define TURNELEMENT_HPP

#include "GameElements/GameElement.hpp"
#include "Primitives/Cube.hpp"
#include "Core/Renderer.hpp"
#include <vector>

class TurnElement : public GameElement
{
public:
    TurnElement();
    ~TurnElement() = default;

    void generate() override;
};

#endif