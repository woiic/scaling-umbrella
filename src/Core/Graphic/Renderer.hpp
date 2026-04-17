#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <string>

#include "Core/CoreStructs.hpp"

class Renderer{

private:

    SDL_Renderer* SDLRenderer;

public:

    SDL_Renderer* GetRenderer(){ return SDLRenderer; }

    Renderer();
    bool PreInit();
    bool Init(SDL_Window *window, WindowData inWindowData);

    void Clear();
    void Present();

    SDL_Color GetSDLColor(int a, int r, int g, int b) {return SDL_Color{ (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };}
    SDL_Color GetSDLColor(const Color& inColor) {return GetSDLColor(inColor.a, inColor.r, inColor.g, inColor.b);}
    
    // SDL FREct||
    SDL_FRect GetSDLFRect(float x, float y, float w, float h) {return SDL_FRect{ (float)x, (float)y, (float)w, (float)h };}
    SDL_FRect GetSDLFRect(FRect inFRect) {return GetSDLFRect(inFRect.x, inFRect.y, inFRect.w, inFRect.h);}
    
    void RenderBackGround(Color inColor);
        
    void DrawRect(Color inColor, FRect inRect);
    bool DrawGeometry(Color inColor, FGeometry inRect);
    
    //bool DrawTexture(FRect inRect, const char* inFilePath,  const char* inFileName);
    //bool DrawTexture(FRect inRect, char* inFilePath,  char* inFileName);
    bool DrawTexture(std::string name);
    
    void Destroy();
};