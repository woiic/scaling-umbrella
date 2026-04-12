#pragma once
#include <string>

struct IPoint
{
    int x=0;
    int y=0;

    IPoint()
    {
        x = 0;
        y = 0;
    }

    IPoint(int a, int b)
    {
        x = a;
        y = b;
    }

    std::string to_string() const {
        return "x: " + std::to_string(x) + ", " + "y: " + std::to_string(y);
    }

    IPoint operator+(const IPoint& other) const {
        return { x + other.x, y + other.y };
    }

    IPoint operator-(const IPoint& other) const {
        return { x - other.x, y - other.y };
    }
};

struct FPoint
{
    float x=0.0f;
    float y=0.0f;

    FPoint()
    {
        x = 0.0f;
        y = 0.0f;
    }

    FPoint(float a, float b)
    {
        x = a;
        y = b;
    }

    std::string to_string() const {
        return "x: " + std::to_string(x) + ", " + "y: " + std::to_string(y);
    }

    FPoint operator+(const FPoint& other) const {
        return { x + other.x, y + other.y };
    }

    FPoint operator-(const FPoint& other) const {
        return { x - other.x, y - other.y };
    }
};

struct MouseState{
    FPoint mousePosition;
    bool bIsLeftJustPressed;
    bool bIsLeftHeld;
    bool bIsLeftJustReleased;
    bool bIsRightJustPressed;
    bool bIsRightHeld;
    bool bIsRightJustReleased;
    MouseState()
    {
        mousePosition = FPoint(0.0f, 0.0f);
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

// -- SDL data Adapters -- //

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
/*
    [x,y] -------> w
                   ||
                   ||                  
                   ||
                   ||
                   ||
                   \/
                   H

*/
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

struct FGeometry {
    float v;
    FGeometry()
    {

    }
};

/*
typedef struct SDL_Vertex
{
    SDL_FPoint position;        /**< Vertex position, in SDL_Renderer coordinates  
    SDL_FColor color;           /**< Vertex color 
    SDL_FPoint tex_coord;       /**< Normalized texture coordinates, if needed 
} SDL_Vertex;
*/
struct Vertex
{
    FPoint position;
    Color color;
    FPoint text_coord;
};

struct Texture
{
    char* path;
    char* file_name;
    int texture_width = 0;
    int texture_height = 0;
};

struct Area2D{
    FPoint position; //upper left
    float width;
    float height;
    Color color;

    Area2D()
    {
        position = FPoint(0.0f, 0.0f);
        width = 0.0f;
        height = 0.0f;
        color = Color();
    }
    Area2D(FPoint inPos, float inWidth, float inHeight, Color inColor)
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