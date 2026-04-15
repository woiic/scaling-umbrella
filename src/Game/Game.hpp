#pragma once

#include "Core/CoreStructs.hpp"
#include "Core/TextureManager.hpp"

#include "Graphic/Renderer.hpp"
#include "GameObject.hpp"
#include "GameEnums.hpp"
#include "BoardStuff/Board.hpp"

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

    GameState LastGameState;
    GameState ActualGameState;

public:
    //Specific game stuff

    Board GameBoard;


// For rendering custom rectangles
public:
    FPoint startPoint;
    FPoint endPoint;

};