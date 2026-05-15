#pragma once

#include <iostream>
#include "TextureManager.hpp"

#include "Renderer.hpp"
#include "Sprite.hpp"
#include "Text.hpp"


std::unordered_map<std::string, Sprite*> TextureManager::spritesTextures;
std::unordered_map<std::string, Text*> TextureManager::textsTextures;

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
    spritesTextures[std::string(name)] = std::move(texture);

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
        LOG_ERROR("error while creating the surface");
        return nullptr;
    }
    SDLtexture = SDL_CreateTextureFromSurface(inRenderer.GetRenderer(), surface);
    if (!SDLtexture)
    {
        LOG_ERROR("error while creating the texture");
        return nullptr;
    }

    Sprite *sprite = new Sprite(path, name, surface->w, surface->h, SDLtexture);
    spritesTextures[ID] = sprite;
    
    SDL_DestroySurface(surface);
    
    return sprite;
}

size_t TextureManager::CountSprites()
{
    return spritesTextures.size();
}


Sprite* TextureManager::GetSprite(const std::string& name)
{
    auto it = spritesTextures.find(name);
    if (it != spritesTextures.end()) {
        return it->second;
    }
    return nullptr;
}

Text* TextureManager::LoadText(Renderer &inRenderer, const char* path, const char* name, Color inColor)
{
    return nullptr;
}

//Text* TextureManager::LoadTextByID(Renderer &inRenderer, std::string ID, std::string path, std::string name)
Text* TextureManager::LoadTextByID(Renderer &inRenderer, std::string ID, std::string path, std::string name, Color inColor)
{
    SDL_Surface *surf = NULL;
    SDL_Texture *SDLtexture = NULL;

    // load the file storing the texts
    std::string string_path = std::string(path) + std::string(name);
    // set the text to show
    std:: string textToShow = "Hello World!";
    surf = TTF_RenderText_Blended(inRenderer.GetFont(), textToShow.c_str(), 0, inColor.GetSDLColor());
    if (!surf) {
        LOG_ERROR("error while creating the surface");
        return nullptr;
    }
    SDLtexture = SDL_CreateTextureFromSurface(inRenderer.GetRenderer(), surf);
    if (!SDLtexture)
    {
        LOG_ERROR("error while creating the texture");
        return nullptr;
    }

    Text* text = new Text(path, name, surf->w, surf->h, SDLtexture);
    textsTextures[ID] = text;

    SDL_DestroySurface(surf);
    return nullptr;
}

size_t TextureManager::CountTexts()
{
    return textsTextures.size();
}


Text* TextureManager::GetText(const std::string& name)
{
    auto it = textures.find(name);
    if (it != textures.end()) {
        //return it->second;
        auto s = it->second;
        return new Sprite(s->path, s->file_name, s->TEXTURE_WIDTH, s->TEXTURE_HEIGHT, s->Get());
    }
    return nullptr;
}


void TextureManager::Clear()
{
    for (auto& [id, sprite] : spritesTextures) {
            delete sprite;
            sprite = nullptr;
        }
        spritesTextures.clear();
}