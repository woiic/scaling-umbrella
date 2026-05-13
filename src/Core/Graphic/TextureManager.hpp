#pragma once

#include <cstring>
#include <memory>
#include <unordered_map>
#include <string>

#include "Core/DEBUG/Logger.hpp"
#include "Core/CoreStructs.hpp"

#include <SDL3/SDL.h>

class Renderer;
class Sprite;
class Text;


class TextureManager {
public:
    
    //static Texture* Load(Renderer &inRenderer, const char* path, const char* name);
    static Sprite* Load(Renderer &inRenderer, const char* path, const char* name);
    static Sprite* LoadByID(Renderer &inRenderer, std::string ID, std::string path, std::string name);

    static Sprite* GetSprite(const std::string& name);
    static size_t CountSprites();
    
    static Text* LoadText(Renderer &inRenderer, const char* path, const char* name, Color inColor);
    static Text* LoadTextByID(Renderer &inRenderer, std::string ID, std::string path, std::string name, Color inColor);

    static Text* GetText(const std::string& name);
    static size_t CountTexts();
    

    static void Clear();

private:

    static std::unordered_map<std::string, Sprite*> spritesTextures;
    static std::unordered_map<std::string, Text*> textsTextures;
    
    
};