#pragma once
#include <iostream>

#include "Core/Graphic/Renderer.hpp"
#include "Core/Graphic/TextureManager.hpp"
#include "Core/Graphic/Sprite.hpp"

#include "GameObject.hpp"

GameObject::GameObject()
{
    ObjectArea2D = Area2D();
    ObjectSprite = nullptr;
}

void GameObject::Update(MouseState inMouseState, float deltaTime)
{
    if (ObjectArea2D.IsMouseOver(inMouseState.mousePosition))
    {
        // Tocar/Tomar pieza (to be determined)
        if (inMouseState.bIsLeftJustPressed)
        {
            std::cout << "objecto clickeado" << std::endl;
            return ;
        }
        if (inMouseState.bIsLeftJustReleased)
        {
            std::cout << "objecto des-clickeado" << std::endl;
            return ;
        }
    }
}

void GameObject::Render(Renderer& inRenderer)
{
    if (ObjectArea2D)
    {
        FRect tempRect = FRect(ObjectArea2D.position.x, ObjectArea2D.position.y, ObjectArea2D.width, ObjectArea2D.height);
        inRenderer.DrawRect(ObjectArea2D.color, tempRect);
    }
}

void GameObject::RenderSprite(Renderer& inRenderer)
{
    inRenderer.DrawSprite(ObjectSprite, ObjectArea2D);
}

IPoint GameObject::GetSpriteWH()
    {
        if (!ObjectSprite) return IPoint(0, 0);
        return IPoint(ObjectSprite->TEXTURE_WIDTH, ObjectSprite->TEXTURE_HEIGHT);
    }

void GameObject::setArea2D(Area2D inArea2D)
{
    ObjectArea2D = inArea2D;
}