#pragma once
#include "../Core/CoreStructs.hpp"
#include <SDL3/SDL.h>

class InputHandler
{
    protected:

    MouseState lastFrameMouseState;
    MouseState actualMouseState;

    public:

    InputHandler();

    MouseState GetMouseState();
    void HandleMouseEvent(const SDL_Event& event);
    bool bEventThisFrame = false;

};