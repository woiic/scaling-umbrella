#pragma once
#include <SDL3/SDL.h>

#include "CoreStructs.hpp"
#include "Input/InputHandler.hpp"
#include "Graphic/Renderer.hpp"

class Game; // forward declaration

// signature
SDL_GPUDevice* SDL_CreateGPUDevice(
  SDL_GPUShaderFormat format_flags,
  bool debug_mode,
  const char *name
);


class Engine {
public:
    Engine();
    ~Engine();

    bool Init(const char* title, int width, int height);
    void Run(Game& inGame);
    void Shutdown();

private:
    MouseState lastFrameMouseState;
    MouseState HandleEvents();
    void Update(float deltaTime);
    void Render(Game *inGame);

private:
    Renderer* renderer;
    SDL_Window* window;

    SDL_GPUDevice* device = nullptr;
    InputHandler* inputHandler = nullptr;

    bool running;

};