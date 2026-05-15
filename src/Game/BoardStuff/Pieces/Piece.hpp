#pragma once

#include "Core/CoreStructs.hpp"
#include "Game/GameObject.hpp"

#include "Game/CommonHeader.hpp"

class Sprite;
class Board;

enum Team {
    NoTeam=0,
    WHITE,
    BLACK
};

enum PieceType{
    NoPiece=0,
    PAWN,
    KNIGHT,
    BISHOP,
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

static std::string TeamToString(Team type) {
    switch (type) {
    case Team::NoTeam:   return "No team";
    case Team::WHITE:    return "white";
    case Team::BLACK:    return "black";
    default:             return "No team";
    }
}

class Piece : public GameObject{
public:
    
    Piece();
    Piece(IPoint inPosition, PieceType inPieceType);

    ~Piece();

    Board* boardRef;

    Team pieceTeam;

    bool bIsFollowingMouse = false;

    // position relative to the board
    IPoint position;
    PieceType pieceType=PieceType::PAWN;


    void Update(MouseState inMouseState, float deltaTime) override;
    void Render(Renderer& inRenderer) override;
    //PlayerController *PlayerOwner;
    //Team pieceOwnerTeam

    // gameplay stuff

    void SetPosition(IPoint inPos);
    void MovePiece(bool bIsValidMovemente);

    void SetSpriteRelativePosition(FPoint inPoint);
    void SetSpriteRelativePosition(IPoint inPoint);


    void FreePositionTile();
    void UpdateArea2DPosition();

    std::vector<IPoint> posiblePositions;
    bool bIsInStartingPosition;
    bool bHasMoved2Tiles = false;

    //std::vector<IPoint> GetPossibleMoves();
    std::vector<IPoint> GetMovesByBehaviour();

};