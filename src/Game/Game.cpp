#pragma once
#include <iostream>

#include "Game.hpp"

Game::Game()
{
}

Game::~Game() 
{
    //Shutdown();
}

void Game::Start()
{
    GameObjectsList = std::vector<GameObject>();
    LastGameState = ActualGameState = GameState::Start;
}

void Game::Update(MouseState inMouseState) 
{
    switch (ActualGameState)
    {
    case GameState::Start:
        if (ActualGameState != LastGameState) //First frame check
        {
            // Init Board
            GameBoard.InitBoard(8, 8);

        }
        LastGameState = ActualGameState;
        break;
    
    default:
        break;
    }
    
    /*
    if (inMouseState.bIsLeftJustPressed) LeftIsJustPressed(inMouseState);
    if (inMouseState.bIsLeftHeld) LeftIsHeld(inMouseState);
    if (inMouseState.bIsLeftJustReleased) LeftIsJustReleased(inMouseState);
    */
    return;
}

void Game::LeftIsJustPressed(MouseState inMouseState)
{
    GameObject tempObj = GameObject();
    tempObj.ObjectArea2D.position = inMouseState.mousePosition;
    tempObj.ObjectArea2D.color = Color(255, 255, 255, 255);
    GameObjectsList.push_back(tempObj);
    FocusedObject = &GameObjectsList.back();
}
void Game::LeftIsHeld(MouseState inMouseState)
{
    if(!FocusedObject) return ;
    FocusedObject->ObjectArea2D.width = inMouseState.mousePosition.x - FocusedObject->ObjectArea2D.position.x;
    FocusedObject->ObjectArea2D.height = inMouseState.mousePosition.y - FocusedObject->ObjectArea2D.position.y;
    endPoint = inMouseState.mousePosition;
}
void Game::LeftIsJustReleased(MouseState inMouseState)
{
    FocusedObject = nullptr;
    endPoint = inMouseState.mousePosition;
}

void Game::Render(Renderer& inRenderer)
{
    Color BGColor = Color(200, 50, 50, 255);
    inRenderer.RenderBackGround(BGColor);
    int cont = 0;
    for (auto& obj : GameObjectsList) {
        obj.Render(inRenderer);
        cont +=1;
    }
}