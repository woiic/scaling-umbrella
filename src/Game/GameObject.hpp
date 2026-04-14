#pragma once
#include "Math/MathUtils.hpp"
#include "Core/CoreStructs.hpp"

class Renderer;

class GameObject
{
protected:

public:
    GameObject();

    Area2D ObjectArea2D;
    virtual void Render(Renderer& inRenderer);

    void setArea2D(Area2D inArea2D);

};