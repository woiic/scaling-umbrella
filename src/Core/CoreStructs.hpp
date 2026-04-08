#pragma once
#include <string>


struct WindowData
{
    const char* title;
    int width;
    int height;
    WindowData(const char* inTitle, int inWidth, int inHeight){
        title = inTitle;
        width = inWidth;
        height = inHeight;
    }
};

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

    std::string to_string() const {
        return "x: " + std::to_string(x) + ", " + "y: " + std::to_string(y);
    }

    Point operator+(const Point& other) const {
        return { x + other.x, y + other.y };
    }

    Point operator-(const Point& other) const {
        return { x - other.x, y - other.y };
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

// ------------------------ RenderingStuff ------------------------ //

struct Color{
    int r;
    int g;
    int b;
    int a;

    Color(int inR=0, int inG=0, int inB=0, int inA=255) {
        r=inR;
        g=inG;
        b=inB;
        a=inA;
    }
};

struct FRect {
    float x;
    float y;
    float w;
    float h;
    FRect(float inX=0, float inY=0, float inW=0, float inH=0) {
        x=inX;
        y=inY;
        w=inW;
        h=inH;
    }
};

struct Area2D{
    Point position; //upper left
    float width;
    float height;
    Color color;
    Area2D()
    {
        position = Point(0.0f, 0.0f);
        width = 0.0f;
        height = 0.0f;
        color = Color();
    }
    Area2D(Point inPos, float inWidth, float inHeight, Color inColor)
    {
        position = inPos;
        width = inWidth;
        height = inHeight;
        color = inColor;
    }
    std::string to_string() const {
    return "Area2D{ pos=(" + position.to_string() + ")"
        + ", w=" + std::to_string(width)
        + ", h=" + std::to_string(height)
        + ", color=(" + std::to_string(color.r) + ", " + std::to_string(color.g) + ", "
        + std::to_string(color.b) + ", " + std::to_string(color.a) + ") }";
    }

    explicit operator bool() const {
        return true;
    }
};