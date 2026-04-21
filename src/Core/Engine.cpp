
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "Input/InputHandler.hpp"

#include "Game/Game.hpp"
#include "Engine.hpp"


Engine::Engine()
    : window(nullptr), renderer(nullptr), running(false), device(nullptr), inputHandler(nullptr) {}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Init(const char* title, int width, int height) {

    WindowData newWindowData = WindowData(title, width, height);
    renderer = new Renderer();
    renderer->PreInit();
    //renderer->Init(window, newWindowData);
    window = renderer->Init(newWindowData);
   
    inputHandler = new InputHandler();
    running = true;
    return true;
}

void Engine::Run(Game& inGame) {
    Uint64 lastTime = SDL_GetTicks();

    //inGame.Start();
    inGame.Start(*renderer);
    while (running) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        MouseState mouseState = HandleEvents();
        Update(deltaTime);
        inGame.Update(mouseState);

        Render(&inGame);
        SDL_Delay(16);  // ~60 FPS
    }
}

MouseState Engine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        else inputHandler->HandleMouseEvent(event);
    }
    MouseState mouseState = inputHandler->GetMouseState();
    return mouseState;
}

void Engine::Update(float deltaTime)
{
    // TODO: Game logic here
}

void Engine::Render(Game *inGame) 
{
    renderer->Clear();
    inGame->Render(*renderer);
    renderer->Present();
    
}

void Engine::Shutdown() {
    if (renderer) {
        //SDL_DestroyRenderer(renderer);
        renderer->Destroy();
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