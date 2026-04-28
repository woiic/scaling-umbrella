#pragma once

#include <iostream>
#include "TextureManager.hpp"

#include "Renderer.hpp"
#include "Sprite.hpp"


std::unordered_map<std::string, Sprite*> TextureManager::textures;
//std::unordered_map<int, Texture*> TextureManager::texturesBUp;

//Texture* TextureManager::Load(const std::string& name, const std::string& path) 
/*
    Do not use, only for testing purposes
*/
Sprite* TextureManager::Load(Renderer &inRenderer, const char* path, const char* name) 
{
    SDL_Surface *surface = NULL;
    SDL_Texture *SDLtexture = NULL;
    Sprite *texture = nullptr;

    std::string png_path = std::string(path) + std::string(name);
    surface = SDL_LoadPNG(png_path.c_str());
    if (!surface)
    {
        std::cout << "surface error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDLtexture = SDL_CreateTextureFromSurface(inRenderer.GetRenderer(), surface);
    if (!SDLtexture)
    {
        std::cout << "texture error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_DestroySurface(surface);
    std::cout << "texture file name: " << std::string(name) << std::endl;
    texture = new Sprite(std::string(path), std::string(name), surface->w, surface->h, SDLtexture);
    textures[std::string(name)] = std::move(texture);

    return texture;
}

Sprite* TextureManager::LoadByID(Renderer &inRenderer, std::string ID, std::string path, std::string name) 
{
    SDL_Surface *surface = NULL;
    SDL_Texture *SDLtexture = NULL;

    std::string png_path = std::string(path) + std::string(name);
    surface = SDL_LoadPNG(png_path.c_str());
    if (!surface)
    {
        std::cout << "surface error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDLtexture = SDL_CreateTextureFromSurface(inRenderer.GetRenderer(), surface);
    if (!SDLtexture)
    {
        std::cout << "texture error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    Sprite *texture = new Sprite(path, name, surface->w, surface->h, SDLtexture);
    textures[ID] = texture;
    
    SDL_DestroySurface(surface);
    
    return texture;
}

size_t TextureManager::Count()
{
    return textures.size();
}


Sprite* TextureManager::Get(const std::string& name)
{
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}

void TextureManager::Clear()
{
    for (auto& [id, sprite] : textures) {
            delete sprite;
            sprite = nullptr;
        }
        textures.clear();
}