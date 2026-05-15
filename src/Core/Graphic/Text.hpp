#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "Core/DEBUG/Logger.hpp"
#include "Core/CoreStructs.hpp"


class Renderer;

class Text
{
public:

    Text(std::string inPath,std::string inFile_name, int inWidth, int inHeight, SDL_Texture* inTexture);
    ~Text();

public: 

    TTF_Font *mFont = nullptr;
    SDL_Texture *mFontTextTexture = nullptr;

    
    std::string path;
    std::string file_name;
    int TEXT_WIDTH = 0;
    int TEXT_HEIGHT = 0;

    SDL_Texture* Get() const{ return SDLtexture; }

    private:
    SDL_Texture *SDLtexture = NULL;    

};

