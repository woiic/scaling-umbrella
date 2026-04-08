#pragma once
#include "Math/MathUtils.hpp"
#include "Core/CoreStructs.hpp"

#include "Graphic/Renderer.hpp"

class GameObject
{
protected:

public:
    GameObject();

    Area2D ObjectArea2D;
    void Render(Renderer& inRenderer);

};