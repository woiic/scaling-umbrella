#pragma once

#include "Core/CoreStructs.hpp"

#include "Game/GameObject.hpp"

enum Team {
    White=0,
    Black
};

enum PieceType{
    NoPiece=0,
    PAWN,
    BISHOP,
    KNIGHT,
    TOWER,
    QUEEN,
    KING
};

class Piece : public GameObject{
public:
    
    Piece();
    Piece(IPoint inPosition, PieceType inPieceType);

    IPoint position;
    PieceType pieceType=PieceType::PAWN;

    void Render(Renderer& inRenderer) override;
    //PlayerController *PlayerOwner;
    //Team pieceOwnerTeam

};