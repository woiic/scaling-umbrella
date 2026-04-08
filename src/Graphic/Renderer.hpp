#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>

#include "Core/CoreStructs.hpp"

class Renderer{

private:

    SDL_Renderer* SDLRenderer;

public:

    Renderer();
    bool PreInit();
    bool Init(SDL_Window *window, WindowData inWindowData);

    void Clear();
    void Present();


    //void DrawRect(SDL_Color inColor, SDL_FRect inRect);
    void DrawRect(Color inColor, FRect inRect);
    //void RenderBackGround(SDL_Color inColor);
    void RenderBackGround(Color inColor);

    SDL_Color GetSDLColor(int a, int r, int g, int b) {return SDL_Color{ (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };}
    SDL_Color GetSDLColor(const Color& inColor) {return GetSDLColor(inColor.a, inColor.r, inColor.g, inColor.b);}

    // SDL FREct||
    SDL_FRect GetSDLFRect(float x, float y, float w, float h) {return SDL_FRect{ (float)x, (float)y, (float)w, (float)h };}
    SDL_FRect GetSDLFRect(FRect inFRect) {return GetSDLFRect(inFRect.x, inFRect.y, inFRect.w, inFRect.h);}

    void Destroy();
};