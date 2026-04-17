#pragma once

#include <cstring>
#include <memory>
#include <unordered_map>
#include <string>

#include <SDL3/SDL.h>

#include "Renderer.hpp"
#include "Texture.hpp"

//class Texture; // your wrapper

class TextureManager {
public:
    
    //static Texture* Load(Renderer &inRenderer, const char* path, const char* name);
    static Texture* Load(Renderer &inRenderer, const char* path, const char* name);
    static Texture* Get(const std::string& name);
    static size_t Count();

/*
    static void Clear();

private:
    static std::unordered_map<std::string, Texture*> textures;
*/
private:

    static std::unordered_map<std::string,Texture*> textures;
    //static std::unordered_map<int,Texture*> texturesBUp;
};