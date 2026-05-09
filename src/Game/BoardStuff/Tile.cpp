#pragma once

#include "Game/BoardStuff/Board.hpp"
#include "Tile.hpp"

Tile::Tile()
{
    boardRef=nullptr;
}

Tile::Tile(IPoint inPosition, Board *inBoardRef)
{
    position = inPosition;
    boardRef = inBoardRef;
}

void Tile::Render(Renderer& inRenderer)
{
    GameObject::Render(inRenderer);
}

void Tile::RenderSprite(Renderer& inRenderer)
{
    GameObject::RenderSprite(inRenderer);

    // tengo que cargar el pointSprite y un circle Sprite
    // Además de setear un Area2D para ambos
    //GameObject::RenderCustomSprite(inRenderer, PointSprite, ObjectArea2D);

}

void Tile::Update(MouseState inMouseState, float deltaTime)
{
    if (ObjectArea2D.IsMouseOver(inMouseState.mousePosition))
    {
        boardRef->SetHoverTile(this);

        /* Moved to Piece.cpp
        if (inMouseState.bIsLeftJustReleased && boardRef->activePiece)
        {
            boardRef->TryToMovePiece(this);
            return ;
        }
        */
    }
    return ;
}