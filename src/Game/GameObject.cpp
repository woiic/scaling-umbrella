#pragma once
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