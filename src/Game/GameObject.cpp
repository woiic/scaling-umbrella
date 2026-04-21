#pragma once

#include "Core/Graphic/Renderer.hpp"
#include "Core/Graphic/TextureManager.hpp"
#include "Core/Graphic/Sprite.hpp"

#include "GameObject.hpp"

GameObject::GameObject()
{
    ObjectArea2D = Area2D();
    ObjectSprite = nullptr;
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

void GameObject::setArea2D(Area2D inArea2D)
{
    ObjectArea2D = inArea2D;
}