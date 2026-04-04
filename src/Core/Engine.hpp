#pragma once
#include <SDL3/SDL.h>
#include "InputHandler.hpp"

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
    void Run();
    void Shutdown();

private:
    void HandleEvents();
    void Update(float deltaTime);
    void Render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_GPUDevice* device = nullptr;
    InputHandler* inputHandler = nullptr;

    bool running;

};