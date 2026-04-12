#pragma once

#include "Math/MathUtils.hpp"
#include <memory>

#include "Tile.hpp"
#include "Pieces/Piece.hpp"


class Board {
public:
    
    Board();
    std::vector<std::unique_ptr<Tile>> TilesBoard;
    
    int boardWidth;
    int boardHeight;
    void InitBoard(int inBoardWidth, int inBoardHeight);

    Tile* getTile(int i, int j){
        return TilesBoard[i * boardWidth + j].get();
    }
    
    std::vector<std::unique_ptr<Piece>> PiecesList;

    void InitPieces();

private:



};