#include <iostream>

#include <cstring>
#include "Core/CoreEnums.hpp"

#include "Renderer.hpp"
#include "Text.hpp"

Text::Text(std::string inPath,std::string inFile_name, int inWidth, int inHeight, SDL_Texture* inTexture)
{
    path = inPath;
    file_name = inFile_name;
    TEXT_WIDTH = inWidth;
    TEXT_HEIGHT = inHeight;
    SDLtexture = inTexture;
}

Text::~Text()
{
    
}
