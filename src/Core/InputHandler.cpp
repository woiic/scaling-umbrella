#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "InputHandler.hpp"
#include "../Math/Scalar.hpp"

InputHandler::InputHandler()
{
    
}

MouseState InputHandler::GetMouseState()
{
    mouseState = MouseState();
    // In your main loop, after SDL_PollEvent()
    float mouseX, mouseY;
    Uint32 buttonState = SDL_GetMouseState(&mouseX, &mouseY);
    mouseState.mousePosition = Point(mouseX, mouseY);
    if (buttonState & SDL_BUTTON_LMASK) mouseState.bIsLeftClicked = true;
    if (buttonState & SDL_BUTTON_RMASK) mouseState.bIsRightClicked = true;
    return mouseState;
}

// when a mouse button has been just clicked
void InputHandler::HandleMouseEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            // Left click
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            // Right click
        }
    }
}