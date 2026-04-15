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

//bool Renderer::DrawTexture(FRect inRect, const char* inFilePath,  const char* inFileName)
//bool Renderer::DrawTexture(FRect inRect, char* inFilePath,  char* inFileName)
bool Renderer::DrawTexture(FRect inRect, std::string inFilePath,  std::string inFileName)
{
    SDL_Texture *texture = NULL;

    SDL_Surface *surface = NULL;
    char* png_path = (char*)inFilePath.c_str();

    SDL_asprintf(&png_path, inFilePath.c_str(), SDL_GetBasePath());  /* allocate a string of the full file path */
    surface = SDL_LoadPNG(png_path);
    if (!surface) {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return false;
    }

    SDL_free(png_path);  /* done with this, the file is loaded. */

    texture = SDL_CreateTextureFromSurface(SDLRenderer, surface);
    if (!texture) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return false;
    }

    SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now. */

    SDL_Vertex vertices[4];

    SDL_zeroa(vertices);
    vertices[0].position.x = inRect.x;
    vertices[0].position.y = inRect.y;
    vertices[0].color.r = vertices[0].color.g = vertices[0].color.b = vertices[0].color.a = 1.0f;
    vertices[0].tex_coord.x = 0.0f;
    vertices[0].tex_coord.y = 0.0f;
    
    vertices[1].position.x = inRect.x + inRect.w;
    vertices[1].position.y = inRect.y;
    vertices[1].color.r = vertices[1].color.g = vertices[1].color.b = vertices[1].color.a = 1.0f;
    vertices[1].tex_coord.x = 1.0f;
    vertices[1].tex_coord.y = 0.0f;
    
    vertices[2].position.x = inRect.x;
    vertices[2].position.y = inRect.y + inRect.h;
    vertices[2].color.r = vertices[2].color.g = vertices[2].color.b = vertices[2].color.a = 1.0f;
    vertices[2].tex_coord.x = 0.0f;
    vertices[2].tex_coord.y = 1.0f;

    vertices[3].position.x = inRect.x + inRect.w;
    vertices[3].position.y = inRect.y + inRect.h;
    vertices[3].color.r = vertices[3].color.g = vertices[3].color.b = vertices[3].color.a = 1.0f;
    vertices[3].tex_coord.x = 1.0f;
    vertices[3].tex_coord.y = 1.0f;

    /* And an index to tell it to reuse some of the vertices between triangles... */
    {
    /* 4 vertices, but 6 actual places they used. Indices need less bandwidth to transfer and can reorder vertices easily! */
    const int indices[] = { 0, 1, 2, 1, 2, 3 };
    SDL_RenderGeometry(SDLRenderer, texture, vertices, 4, indices, SDL_arraysize(indices));
    }

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