#include "TextureManager.hpp"


TextureManager::TextureManager()
{
    
}
/*
std::unordered_map<std::string, Texture*> TextureManager::textures;

Texture* TextureManager::Load(const std::string& name, const std::string& path) {
    if (textures.count(name)) return textures[name];

    Texture* tex = new Texture(path); // internally loads SDL_Texture
    textures[name] = tex;
    return tex;
}

Texture* TextureManager::Get(const std::string& name) {
    return textures.count(name) ? textures[name] : nullptr;
}

void TextureManager::Clear() {
    for (auto& [name, tex] : textures) {
        delete tex;
    }
    textures.clear();
}
    */