#pragma once
#include <iostream>

#include "Renderer.hpp"

Renderer::Renderer()
{
}

bool Renderer::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    return true;
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(SDLRenderer, 25, 25, 25, 255);
    SDL_RenderClear(SDLRenderer);
};

void Renderer::Present()
{
    SDL_RenderPresent(SDLRenderer);
}

void Renderer::DrawRect(SDL_Color inColor, SDL_FRect inRect)
{
    SDL_SetRenderDrawColor(SDLRenderer, inColor.r, inColor.g, inColor.b, inColor.a);
    SDL_RenderFillRect(SDLRenderer, &inRect);
    return ;
}

void Renderer::RenderBackGround(SDL_Color inColor)
{
    SDL_FRect rect = { 350.0f, 250.0f, 100.0f, 100.0f };
    SDL_SetRenderDrawColor(SDLRenderer, 200, 50, 50, 255);
    SDL_RenderFillRect(SDLRenderer, &rect);
}

SDL_Color Renderer::GetColor(int a, int r, int g, int b)
{
    SDL_Color BGColor = SDL_Color();
    BGColor.a = a;
    BGColor.r = r;
    BGColor.g = g;
    BGColor.b = b;

    return BGColor;
}

void Renderer::Destroy()
{
    SDL_DestroyRenderer(SDLRenderer);
}