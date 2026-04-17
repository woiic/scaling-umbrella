#pragma once

#include <iostream>
#include "TextureManager.hpp"

std::unordered_map<std::string, Texture*> TextureManager::textures;
//std::unordered_map<int, Texture*> TextureManager::texturesBUp;

//Texture* TextureManager::Load(const std::string& name, const std::string& path) 
Texture* TextureManager::Load(Renderer &inRenderer, const char* path, const char* name) 
{
    /*
    std::cout << path << std::endl;
    std::cout << name << std::endl;
    SDL_Surface *surface = NULL;
    SDL_Texture *SDLtexture = NULL;
    Texture *texture = nullptr;
    char* temp_name = new char[strlen(name) + 1];
    strcpy_s(temp_name, strlen(name) + 1, name);
    
    char* temp_path = new char[strlen(path) + 1];
    strcpy_s(temp_path, strlen(path) + 1, path);
    
    std::cout << temp_path << std::endl;
    std::cout << temp_name << std::endl;
    
    SDL_asprintf(&temp_path, "%s64xMan.png");
    surface = SDL_LoadPNG(temp_path);
    if (!surface) {
        std::cout << "surface error" << std::endl;
        //SDL_Log("Couldn't load png: %s", SDL_GetError());
        delete[] temp_name; // required
        delete[] temp_path; // required
        delete texture;
        return nullptr;
        }
        
        SDL_free(temp_path);  
        
        int TEXTURE_WIDTH = surface->w;
        int TEXTURE_HEIGHT = surface->h;
        
        //texture->TEXTURE_WIDTH = surface->w;
        //texture->TEXTURE_HEIGHT = surface->h;
        //texture->SDLtexture = SDL_CreateTextureFromSurface(inRenderer.GetRenderer(), surface);
        SDLtexture = SDL_CreateTextureFromSurface(inRenderer.GetRenderer(), surface);

        if (!SDLtexture) {
            //SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        std::cout << "texture error" << std::endl;
        delete[] temp_name; // required
        delete[] temp_path; // required
        SDL_DestroySurface(surface); // SDL3
        delete SDLtexture;
        return nullptr;
        }
        
        SDL_DestroySurface(surface);  
        texture = new Texture(path, name, TEXTURE_WIDTH, TEXTURE_HEIGHT, SDLtexture);
        delete[] temp_name; // required
        delete[] temp_path; // required
        textures[name] = std::move(texture);
        
        return texture;
        return nullptr;
        */
    SDL_Surface *surface = NULL;
    SDL_Texture *SDLtexture = NULL;
    Texture *texture = nullptr;

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

    //SDL_DestroySurface(surface);
    std::cout << "texture file name: " << std::string(name) << std::endl;
    texture = new Texture(std::string(path), std::string(name), surface->w, surface->h, SDLtexture);
    textures[std::string(name)] = std::move(texture);

    return texture;
}

size_t TextureManager::Count()
{
    return textures.size();
}


Texture* TextureManager::Get(const std::string& name)
{
    if(textures.count(name))
    {
        return textures[name];
    }
    return nullptr;
}