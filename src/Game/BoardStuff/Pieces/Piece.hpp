#pragma once

#include "Core/CoreStructs.hpp"
#include "Game/GameObject.hpp"

#include "Game/CommonHeader.hpp"

enum Team {
    NoTeam=0,
    WHITE,
    BLACK
};

enum PieceType{
    NoPiece=0,
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING
};

class Piece : public GameObject{
public:
    
    Piece();
    Piece(IPoint inPosition, PieceType inPieceType);

    Team pieceTeam;

    IPoint position;
    PieceType pieceType=PieceType::PAWN;

    void Update(MouseState inMouseState, float deltaTime) override;
    void Render(Renderer& inRenderer) override;
    //PlayerController *PlayerOwner;
    //Team pieceOwnerTeam

};