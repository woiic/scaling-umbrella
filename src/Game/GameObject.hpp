#pragma once

#include "CommonHeader.hpp"
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

    virtual void Update(MouseState inMouseState, float deltaTime);
    void setArea2D(Area2D inArea2D);


public:

    void RenderSprite(Renderer& inRenderer);
    IPoint GetSpriteWH();

};