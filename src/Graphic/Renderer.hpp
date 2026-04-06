#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>

class Renderer{

private:

    SDL_Renderer* SDLRenderer;

public:

    Renderer();
    bool Init();

    void Clear();
    void Present();

    void DrawRect(SDL_Color inColor, SDL_FRect inRect);
    void RenderBackGround(SDL_Color inColor);

    SDL_Color GetColor(int a, int r, int g, int b);

    void Destroy();
};