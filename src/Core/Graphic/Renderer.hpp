#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "Core/DEBUG/Logger.hpp"
#include "Core/Graphic/TextureManager.hpp"
#include "Core/Graphic/Sprite.hpp"
#include "Core/Graphic/Text.hpp"
#include "Core/CoreStructs.hpp"


class Renderer{

private:

    SDL_Renderer* SDLRenderer;

public:

    SDL_Renderer* GetRenderer(){ return SDLRenderer; }

    Renderer();
    bool PreInit();
    
    SDL_Window* Init(WindowData inWindowData);

public:

    // Sprites and renders

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
    
    bool DrawSprite(Sprite* inSprite, Area2D inArea2D);

    bool DrawText(Text* inText, Area2D inArea2D);

public:
    // text stuff 
    bool InitText();

    TTF_Font* GetFont() {return mFont; }

    TTF_Font *mFont = nullptr;

public:

    void Destroy();
};