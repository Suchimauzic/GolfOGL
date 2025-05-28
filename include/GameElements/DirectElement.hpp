#ifndef DIRECTELEMENT_HPP
#define DIRECTELEMENT_HPP

#include "GameElements/GameElement.hpp"
#include "Primitives/Cube.hpp"
#include "Core/Renderer.hpp"
#include <vector>

class DirectElement : public GameElement
{
public:
    DirectElement();
    ~DirectElement() = default;

    void generate() override;
};

#endif