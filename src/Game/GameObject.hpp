#pragma once
#include "Math/MathUtils.hpp"
#include "Core/CoreStructs.hpp"


class Renderer;
class Sprite;

class GameObject
{
protected:

public:
    GameObject();

    Area2D ObjectArea2D;
    
    Sprite* ObjectSprite;

    virtual void Render(Renderer& inRenderer);

    void setArea2D(Area2D inArea2D);

public:
// testing only
    void RenderSprite(Renderer& inRenderer);
};