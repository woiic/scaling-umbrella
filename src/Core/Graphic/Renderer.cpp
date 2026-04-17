#pragma once
#include <iostream>

#include <cstring>
#include "Core/CoreEnums.hpp"
#include "Core/Graphic/TextureManager.hpp"
#include "Core/Graphic/Texture.hpp"

#include "Renderer.hpp"

Renderer::Renderer()
{
}

bool Renderer::PreInit()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 1;
}

bool Renderer::Init(SDL_Window *window, WindowData inWindowData)
{
    if (!SDL_CreateWindowAndRenderer("examples/renderer/rectangles", inWindowData.width, inWindowData.height, SDL_WINDOW_RESIZABLE, &window, &SDLRenderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderLogicalPresentation(SDLRenderer, inWindowData.width, inWindowData.height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return true;
}

void Renderer::Clear()
{
    bool output = SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
    SDL_RenderClear(SDLRenderer);
};

void Renderer::Present()
{
    SDL_RenderPresent(SDLRenderer);
}

//void Renderer::DrawRect(SDL_Color inColor, SDL_FRect inRect)
void Renderer::DrawRect(Color inColor, FRect inRect)
{
    
    SDL_FRect tRect = GetSDLFRect(inRect);
    SDL_SetRenderDrawColor(SDLRenderer, inColor.r, inColor.g, inColor.b, inColor.a);
    
    SDL_RenderFillRect(SDLRenderer, &tRect);
    //SDL_RenderRect(SDLRenderer, &tRect);
}

bool Renderer::DrawGeometry(Color inColor, FGeometry inRect)
{
    return true;
}

bool Renderer::DrawTexture(std::string name)
{
    Texture* tempTexture = TextureManager::Get(name);
    if(!tempTexture)
    {
        std::cerr << "Textures amount: " << TextureManager::Count() << std::endl;
        std::cerr << "Texture error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_FRect tempRect
    {
        tempRect.x=0.0f,
        tempRect.y=0.0f,
        tempRect.w=(float)tempTexture->TEXTURE_WIDTH,
        tempRect.h=(float)tempTexture->TEXTURE_WIDTH
    };
    SDL_RenderTexture(SDLRenderer, tempTexture->Get(), NULL, &tempRect);
    return true;
}

//void Renderer::RenderBackGround(SDL_Color inColor)
void Renderer::RenderBackGround(Color inColor)
{
    SDL_SetRenderDrawColor(SDLRenderer, inColor.r, inColor.g, inColor.b, inColor.a);
    SDL_RenderClear(SDLRenderer);
}

void Renderer::Destroy()
{
    SDL_DestroyRenderer(SDLRenderer);
}