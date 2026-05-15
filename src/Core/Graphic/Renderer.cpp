#pragma once
#include <iostream>

#include <cstring>
#include "Core/CoreEnums.hpp"


#include "Renderer.hpp"

Renderer::Renderer()
{
}

bool Renderer::PreInit()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

//bool Renderer::Init(SDL_Window *window, WindowData inWindowData)
SDL_Window* Renderer::Init(WindowData inWindowData)
{
    SDL_Window* window;
    if (!SDL_CreateWindowAndRenderer(
        "examples/renderer/rectangles",
        inWindowData.width,
        inWindowData.height,
        SDL_WINDOW_RESIZABLE,
        &window,
        &SDLRenderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return nullptr;
    }
    SDL_SetRenderLogicalPresentation(SDLRenderer, inWindowData.width, inWindowData.height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    InitText();
    
    return window;
}

bool Renderer::InitText()
{

    if (!TTF_Init()) {
        LOG_ERROR("TTF_Init failed: ");
        LOG_ERROR(SDL_GetError());    
        return false;
    }

        /* Open the font */

    mFont = TTF_OpenFont("assets/Fonts/Arial_Black.ttf", 16.0f);
    if (!mFont)
    {
        LOG_ERROR("TTF font failed to load");
        return false;
    }
    
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

//bool Renderer::DrawSprite(Sprite* inSprite)
bool Renderer::DrawSprite(Sprite* inSprite, Area2D inArea2D)
{
    if (!inSprite)
    {
        //std::cerr << "Textures amount: " << TextureManager::CountSprites() << std::endl;
        //std::cerr << "Texture error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_FRect tempRect
    {
        tempRect.x=inArea2D.position.x + inSprite->relativePosition.x,
        tempRect.y=inArea2D.position.y + inSprite->relativePosition.y,
        tempRect.w=(float)inSprite->TEXTURE_WIDTH,
        tempRect.h=(float)inSprite->TEXTURE_HEIGHT
    };
    SDL_RenderTexture(SDLRenderer, inSprite->Get(), NULL, &tempRect);
    return true;
}

bool Renderer::DrawText(Text* inText, Area2D inArea2D)
{
    
    if (!inText)
    {
        return false;
    }
    SDL_FRect tempRect
    {
        tempRect.x=inArea2D.position.x,// + inText->relativePosition.x,
        tempRect.y=inArea2D.position.y,// + inText->relativePosition.y,
        tempRect.w=(float)inText->TEXT_WIDTH,
        tempRect.h=(float)inText->TEXT_HEIGHT
    };
    SDL_RenderTexture(SDLRenderer, inText->Get(), NULL, &tempRect);
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