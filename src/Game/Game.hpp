#pragma once

#include "Core/CoreStructs.hpp"
#include "Graphic/Renderer.hpp"
#include "GameObject.hpp"
#include "Math/MathUtils.hpp"


class Game {
public:
    Game();
    ~Game();


    void Start();

    void Update(MouseState mouseState);
    
    void LeftIsJustPressed(MouseState inMouseState);
    void LeftIsHeld(MouseState inMouseState);
    void LeftIsJustReleased(MouseState inMouseState);

    void Render(Renderer &inRenderer);

public:

    std::vector<GameObject> GameObjectsList;
    GameObject *FocusedObject;

// For rendering custom rectangles
public:
    Point startPoint;
    Point endPoint;

};