#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "InputHandler.hpp"
#include "Math/MathUtils.hpp"

InputHandler::InputHandler()
{
    
}

MouseState InputHandler::GetMouseState()
{
    if (bEventThisFrame) 
    {
        bEventThisFrame = false;
        return actualMouseState;
    }

    actualMouseState = MouseState();
    
    float mouseX, mouseY;
    Uint32 buttonState = SDL_GetMouseState(&mouseX, &mouseY);
    actualMouseState.mousePosition = FPoint(mouseX, mouseY);
    if (buttonState & SDL_BUTTON_LMASK) actualMouseState.bIsLeftHeld = true;
    if (buttonState & SDL_BUTTON_RMASK) actualMouseState.bIsRightHeld = true;

    return actualMouseState;
}

// when a mouse button has been just clicked
void InputHandler::HandleMouseEvent(const SDL_Event& event) {
    actualMouseState = MouseState();

    float mouseX, mouseY;
    Uint32 buttonState = SDL_GetMouseState(&mouseX, &mouseY);
    actualMouseState.mousePosition = FPoint(mouseX, mouseY);

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            bEventThisFrame = true;
            actualMouseState.bIsLeftJustPressed = true;
            //mouseState.bIsLeftHeld = true;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            bEventThisFrame = true;
            actualMouseState.bIsRightJustPressed = true;
            //mouseState.bIsRightHeld = true;
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            bEventThisFrame = true;
            actualMouseState.bIsLeftJustReleased = true;
            //mouseState.bIsLeftHeld = true;
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            bEventThisFrame = true;
            actualMouseState.bIsRightJustReleased = true;
            //mouseState.bIsRightHeld = true;
        }
    }
}