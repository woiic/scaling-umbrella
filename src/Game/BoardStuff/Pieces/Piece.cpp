#pragma once

#include "Core/DEBUG/Logger.hpp"
#include "Game/BoardStuff/Board.hpp"
#include "Piece.hpp"

Piece::Piece()
{
    pieceTeam = Team::NoTeam;
    position = IPoint();
    pieceType = PieceType::NoPiece;

}

Piece::Piece(IPoint inPosition, PieceType inPieceType)
{
    position = inPosition;
    pieceType = inPieceType;

}

void Piece::Update(MouseState inMouseState, float deltaTime)
{
    if (ObjectArea2D.IsMouseOver(inMouseState.mousePosition))
    {
        // Tocar/Tomar pieza (to be determined)
        if (inMouseState.bIsLeftJustPressed)
        {
            LOG_DEBUG("objecto clickeado");
            bIsFollowingMouse = true;
            boardRef->SetActivePiece(this);
            return ;
        }
        if (inMouseState.bIsLeftHeld && bIsFollowingMouse)
        {
            ObjectArea2D.position = inMouseState.mousePosition;
        }
        if (inMouseState.bIsLeftJustReleased)
        {
            LOG_DEBUG("objecto des-clickeado");
            bIsFollowingMouse = false;
            boardRef->SetActivePiece(nullptr);

            UpdateArea2DPosition();
            return ;
        }
    }

    if (bIsFollowingMouse)
    {
        FPoint temp = (FPoint)GetSpriteWH();
        FPoint fixedPos = inMouseState.mousePosition - temp/2.0f;
        ObjectArea2D.position = fixedPos;
    }
}

void Piece::Render(Renderer& inRenderer)
{
    //GameObject::Render(inRenderer);
}


void Piece::SetPosition(IPoint inPos)
{
    position = inPos;
}

void Piece::FreePositionTile()
{
    boardRef->FreePieceTile(position);
}

void Piece::UpdateArea2DPosition()
{
    FPoint temp = (FPoint)GetSpriteWH();
    FPoint fixedPos = (FPoint)(position * IPoint(boardRef->TILE_WIDTH, boardRef->TILE_HEIGHT)) + temp/2.0f;
    LOG_DEBUG(fixedPos.to_string());
    ObjectArea2D.position = fixedPos;
}