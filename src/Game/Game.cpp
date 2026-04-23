#pragma once

#include "Game.hpp"

Game::Game()
{
}

Game::~Game() 
{
}

//void Game::Start()
void Game::Start(Renderer& inRenderer)
{
    GameObjectsList = std::vector<GameObject>();
    LastGameState = GameState::None;
    ActualGameState = GameState::Initializing;

    LastTurnState = TurnsState::NONE;
    ActualTurnState = TurnsState::NONE;
    LoadSprites(inRenderer);
}

void Game::Update(MouseState inMouseState, float deltaTime) 
{
    switch (ActualGameState)
    {
    case GameState::Initializing:
    {
        if (ActualGameState != LastGameState) //First frame check
        {
            // Init Board
            
            LastGameState = ActualGameState;
        }
        ActualGameState = GameState::Start;
        break;
    }
    case GameState::Start:
        if (ActualGameState != LastGameState) //First frame check
        {
            // Init Board
            GameBoard.InitBoard(8, 8, 16, 16);
            GameBoard.InitPieces();

            LastGameState = ActualGameState;
            ActualGameState = GameState::InGame;

            LastTurnState = TurnsState::NONE;
            ActualTurnState = TurnsState::White;
        }
        break;
    
    case GameState::InGame:
        if (ActualGameState != LastGameState) //First frame check
        {
            
            LastGameState = ActualGameState;
        }

        break;
    default:
        break;
    }
    
    GameBoard.Update(inMouseState, deltaTime);

    /*
    if (inMouseState.bIsLeftJustPressed) LeftIsJustPressed(inMouseState);
    if (inMouseState.bIsLeftHeld) LeftIsHeld(inMouseState);
    if (inMouseState.bIsLeftJustReleased) LeftIsJustReleased(inMouseState);
    */
    return;
}
// Clicking Testing
/*
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
*/


void Game::LoadSprites(Renderer& inRenderer)
{
    std::string ID = "assets/Sprites/white_tile.png";
    std::string path = "assets/Sprites/";
    std::string w_name = "white_tile.png";
    std::string b_name = "black_tile.png";
    TextureManager::LoadByID(inRenderer, ID, path, w_name);
    ID = "assets/Sprites/black_tile.png";
    TextureManager::LoadByID(inRenderer, ID, path, b_name);
    ID = "assets/Sprites/black_pawn.png";
    std::string name = "black_pawn.png";
    TextureManager::LoadByID(inRenderer, ID, path, name);
    ID = "assets/Sprites/white_pawn.png";
    name = "white_pawn.png";
    TextureManager::LoadByID(inRenderer, ID, path, name);
    /*
    auto tiles = j["Sprites"]["Tiles"];
    auto path = tiles["sprite_folder"];
    auto names = tiles["sprite_names"];
    
    std::cout << names["White"] << std::endl;
    std::cout << path << std::endl;
    if (names["White"].is_string() && path.is_string())
    {
        std::string ID = "Tiles/" + names["White"];
        TextureManager::LoadByID(inRenderer, ID, (std::string)path, (std::string)names["White"]);
    }
    std::cout << names["Black"] << std::endl;
    std::cout << path << std::endl;
    if (names["Black"].is_string() && path.is_string())
    {
        std::string ID = "Tiles/" + names["Black"];
        TextureManager::LoadByID(inRenderer, ID, (std::string)path, (std::string)names["Black"]);
    }
    */  
}

void Game::Render(Renderer& inRenderer)
{
    Color BGColor = Color(245, 245, 220, 255);
    inRenderer.RenderBackGround(BGColor);

    GameBoard.Render(inRenderer);
    // Render one texture    

}