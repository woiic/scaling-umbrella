#pragma once

#include "Core/CoreStructs.hpp"

enum Team {
    White=0,
    Black
};

enum PieceType{
    Pawn=0,
    Bishop,
    Knight,
    Tower,
    Queen,
    King
};

class Piece {
public:
    
    Piece();

    FPoint position;
    //PlayerController *PlayerOwner;
    //Team pieceOwnerTeam

    PieceType pieceType=PieceType::Pawn;

};