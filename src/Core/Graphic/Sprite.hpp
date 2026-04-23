#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "Core/CoreStructs.hpp"

class Sprite
{
public:
    Sprite(std::string inPath,std::string file_name, int inWidth, int inHeight, SDL_Texture* inTexture);
    ~Sprite();

    std::string path;
    std::string file_name;
    int TEXTURE_WIDTH = 0;
    int TEXTURE_HEIGHT = 0;

    SDL_Texture* Get() const{ return SDLtexture; }

    private:
    SDL_Texture *SDLtexture = NULL;    

};