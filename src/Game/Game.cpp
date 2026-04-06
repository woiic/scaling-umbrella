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

}

void Game::Update(MouseState inMouseState) 
{
    if (inMouseState.bIsLeftJustPressed) LeftIsJustPressed();
    if (inMouseState.bIsLeftHeld) LeftIsHeld();
    if (inMouseState.bIsLeftJustPressed) LeftIsJustReleased();

    return;
}

void Game::LeftIsJustPressed()
{

}
void Game::LeftIsHeld()
{
}
void Game::LeftIsJustReleased()
{
}

void Game::Render(Renderer& inRender)
{
    SDL_Color BGColor = inRender.GetColor(255, 200, 50, 50);
    inRender.RenderBackGround(BGColor);
    
}