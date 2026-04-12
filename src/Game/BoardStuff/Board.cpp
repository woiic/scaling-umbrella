#pragma once
//#include <nlohmann/json.hpp>

//using json = nlohmann::json;

#include "Board.hpp"

Board::Board()
{

}

/*
    |
    Height
    |
    ---- width ----
    Makes a single vector filled with Tiles -> Tiles[i][j] == Tiles[i*boardWidth + j]
*/
void Board::InitBoard(int inBoardWidth, int inBoardHeight)
{
    // Create board
    boardWidth = inBoardWidth;
    boardHeight = inBoardHeight;
    
    for(int i=0; i<inBoardWidth; i++)
    {
        for(int j=0; j<inBoardWidth; j++)
        {
            //Tile newTile = Tile(FPoint(i, j), this);
            TilesBoard.push_back(std::make_unique<Tile>(IPoint(i, j), this));
        }   
    }

    // Add pieces to the board
    InitPieces();
}

void Board::InitPieces()
{


}