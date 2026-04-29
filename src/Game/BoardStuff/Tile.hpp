#pragma once

#include "Game/CommonHeader.hpp"
#include "Game/GameObject.hpp"

#include "Core/CoreStructs.hpp"
#include "Pieces/Piece.hpp"

class Board;

class Tile : public GameObject {

public:
    Tile();
    Tile(IPoint inPosition, Board *inBoardRef);

    Board *boardRef = nullptr;

    void Update(MouseState inMouseState, float deltaTime) override;
    void Render(Renderer& inRenderer) override;

public:

    IPoint position;
    void SetPosition(IPoint inPos) {position = inPos;}

    //std::unique_ptr<Piece> AssignedPiece = nullptr;
    Piece* AssignedPiece = nullptr;
    //void setPiece(std::unique_ptr<Piece> p) {
    void setPiece(Piece* p) { AssignedPiece = p; }
};
