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
    KING,
};

static std::string PieceTypeToString(PieceType type) {
    switch (type) {
    case PieceType::PAWN:   return "pawn";
    case PieceType::BISHOP: return "bishop";
    case PieceType::KNIGHT: return "knight";
    case PieceType::ROOK:   return "rook";
    case PieceType::QUEEN:  return "queen";
    case PieceType::KING:   return "king";
    default:                return "Unknown";
    }
}

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