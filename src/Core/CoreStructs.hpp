#pragma once
#include <string>

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
    bool bIsLeftJustPressed;
    bool bIsLeftHeld;
    bool bIsLeftJustReleased;
    bool bIsRightJustPressed;
    bool bIsRightHeld;
    bool bIsRightJustReleased;
    MouseState()
    {
        mousePosition = Point(0.0f, 0.0f);
        bIsLeftJustPressed = false;
        bIsLeftHeld = false;
        bIsLeftJustReleased = false;
        bIsRightJustPressed = false;
        bIsRightHeld = false;
        bIsRightJustReleased = false;
    }

    std::string to_string() const {
        return "MouseState{ pos=(" + std::to_string(mousePosition.x) + ", " + std::to_string(mousePosition.y) + ")" +
               ", LeftHeld=" + (bIsLeftHeld ? "true" : "false") +
               ", LeftJustPressed=" + (bIsLeftJustPressed ? "true" : "false") +
               ", RightHeld=" + (bIsRightHeld ? "true" : "false") +
               ", RightJustPressed=" + (bIsRightJustPressed ? "true" : "false") +
               " }";
    }
};


