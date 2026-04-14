#pragma once

#include "Piece.hpp"

Piece::Piece()
{
    position = IPoint();
    pieceType = PieceType::NoPiece;

}

Piece::Piece(IPoint inPosition, PieceType inPieceType)
{
    position = inPosition;
    pieceType = inPieceType;

}

void Piece::Render(Renderer& inRenderer)
{
    //GameObject::Render(inRenderer);
}