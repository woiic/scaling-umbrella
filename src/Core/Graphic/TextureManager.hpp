#pragma once

#include <cstring>
#include <memory>
#include <unordered_map>
#include <string>

#include <SDL3/SDL.h>

class Renderer;
class Sprite; // your wrapper

class TextureManager {
public:
    
    //static Texture* Load(Renderer &inRenderer, const char* path, const char* name);
    static Sprite* Load(Renderer &inRenderer, const char* path, const char* name);
    static Sprite* LoadByID(Renderer &inRenderer, std::string ID, std::string path, std::string name);

    static Sprite* Get(const std::string& name);
    static size_t Count();

/*
    static void Clear();

private:
    static std::unordered_map<std::string, Texture*> textures;
*/
private:

    static std::unordered_map<std::string,Sprite*> textures;
    //static std::unordered_map<int,Texture*> texturesBUp;
};