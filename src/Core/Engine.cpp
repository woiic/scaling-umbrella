
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "InputHandler.hpp"
#include "Engine.hpp"


Engine::Engine()
    : window(nullptr), renderer(nullptr), running(false), device(nullptr) {}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create GPU device (optional, for rendering)
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, nullptr);
    if (device) {
        SDL_ClaimWindowForGPUDevice(device, window);
    }
    inputHandler = new InputHandler();
    running = true;
    return true;
}

void Engine::Run() {
    Uint64 lastTime = SDL_GetTicks();

    while (running) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        HandleEvents();
        Update(deltaTime);
        Render();
        SDL_Delay(16);  // ~60 FPS
    }
}

void Engine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        else inputHandler->HandleMouseEvent(event);
    }
    MouseState mouseState = inputHandler->GetMouseState();
    std::cout << mouseState.mousePosition.x << std::endl;
}

void Engine::Update(float deltaTime) {
    // TODO: Game logic here
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    SDL_RenderClear(renderer);

    SDL_FRect rect = { 350.0f, 250.0f, 100.0f, 100.0f };
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void Engine::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (device) {
        SDL_DestroyGPUDevice(device);
    }

    if (inputHandler)
    {
        inputHandler = nullptr;
    }

    SDL_Quit();
}