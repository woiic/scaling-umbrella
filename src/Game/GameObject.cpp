#pragma once

#include "Graphic/Renderer.hpp"

#include "GameObject.hpp"

GameObject::GameObject()
{
    ObjectArea2D = Area2D();
}

void GameObject::Render(Renderer& inRenderer)
{
    if (ObjectArea2D)
    {
        FRect tempRect = FRect(ObjectArea2D.position.x, ObjectArea2D.position.y, ObjectArea2D.width, ObjectArea2D.height);
        inRenderer.DrawRect(ObjectArea2D.color, tempRect);
        /*
        std::string path = "assets/Sprites/";
        std::string fileName = "64xMan.png";
        inRenderer.DrawTexture(tempRect, path, fileName);
        */
    }
}

void GameObject::setArea2D(Area2D inArea2D)
{
    ObjectArea2D = inArea2D;
}