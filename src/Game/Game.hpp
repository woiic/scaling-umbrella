#pragma once
#include namespace std

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
    
    void LeftIsJustPressed();
    void LeftIsHeld();
    void LeftIsJustReleased();

    void Render(Renderer &inRender);

public:

    vector<GameObject> ;

};