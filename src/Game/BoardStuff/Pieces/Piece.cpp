#pragma once

#include "Core/DEBUG/Logger.hpp"
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
            return ;
        }
        if (inMouseState.bIsLeftJustReleased)
        {
            LOG_DEBUG("objecto des-clickeado");
            return ;
        }
    }
}

void Piece::Render(Renderer& inRenderer)
{
    //GameObject::Render(inRenderer);
}