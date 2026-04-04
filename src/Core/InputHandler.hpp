#pragma once

#include <SDL3/SDL.h>

struct Point
{
    float x=0.0f;
    float y=0.0f;

    Point()
    {
        x = 0.0f;
        y = 0.0f;
    }

    Point(float a, float b)
    {
        x = a;
        y = b;
    }
};

struct MouseState{
    Point mousePosition;
    bool bIsLeftClicked;
    bool bIsRightClicked;
    MouseState()
    {
        mousePosition = Point(0.0f, 0.0f);
        bIsLeftClicked = false;
        bIsRightClicked = false;
    }
};


class InputHandler
{
    protected:

    MouseState mouseState;

    public:

    InputHandler();

    MouseState GetMouseState();
    void HandleMouseEvent(const SDL_Event& event);

};