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
        void Renderer::DrawRect(SDL_Color inColor, SDL_FRect inRect)
        {
            SDL_SetRenderDrawColor(SDLRenderer, inColor.r, inColor.g, inColor.b, inColor.a);
            SDL_RenderFillRect(SDLRenderer, &inRect);
            return ;
        }
        */

    }
}