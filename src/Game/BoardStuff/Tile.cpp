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

void Tile::Update(MouseState inMouseState, float deltaTime)
{
    if (ObjectArea2D.IsMouseOver(inMouseState.mousePosition))
    {
        boardRef->SetHoverTile(this);
        
        if (inMouseState.bIsLeftJustReleased)
        {
            if(!AssignedPiece)
            {
                LOG_DEBUG("actualizada la pieza 1");
                Piece* tempPointer = boardRef->activePiece;
                if(tempPointer) 
                {
                    LOG_DEBUG("actualizada la pieza 2");
                    LOG_DEBUG(position.to_string());

                    boardRef->FreePieceTile(tempPointer->position);                    
                    tempPointer->SetPosition(position);
                    AssignedPiece = tempPointer;
                }
            }
            return ;
        }
    }
    return ;
}