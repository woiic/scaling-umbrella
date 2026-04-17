#pragma once

#include "Texture.hpp"


Texture::Texture(std::string inPath,std::string inFile_name, int inWidth, int inHeight, SDL_Texture* inTexture)
{
    path = inPath;
    file_name = inFile_name;
    TEXTURE_WIDTH = inWidth;
    TEXTURE_HEIGHT = inHeight;
    SDLtexture = inTexture;

}

Texture::~Texture() {
    if (SDLtexture) {
        SDL_DestroyTexture(SDLtexture);
    }
}