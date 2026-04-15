#pragma once


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
void Board::InitBoard(int inBoardWidth, int inBoardHeight, int inTileWidth, int inTileHeight)
{
    // Create board

    TILE_WIDTH = inTileWidth;
    TILE_HEIGHT = inTileHeight;

    boardWidth = inBoardWidth;
    boardHeight = inBoardHeight;
    
    for(int i=0; i<inBoardHeight; i++)
    {
        for(int j=0; j<inBoardWidth; j++)
        {
            //Tile newTile = Tile(FPoint(i, j), this);
            std::unique_ptr<Tile> ptr = std::make_unique<Tile>(IPoint(i, j), this);

            Color c;
            if ((i+j)%2 == 0) c = Color(255,255,255);
            else c = Color(0,0,0);
            Area2D tempArea2D = Area2D(FPoint((float)(j*TILE_WIDTH), (float)(i*TILE_HEIGHT)), (float)TILE_WIDTH, (float)TILE_HEIGHT, c);
            ptr->setArea2D(tempArea2D);

            TilesBoard.push_back(std::move(ptr));
        }   
    }
    
    // Add pieces to the board
}

void Board::InitPieces()
{
    std::ifstream file("data/boards/PiecesConfig.json");
    if (!file.is_open()) {
        // handle error (log, return, etc.)
        std::cerr << "Failed to open file\n";
        return;
    }

    json j;
    try {
        file >> j;
    } catch (const std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
    }

    AddPieces(j);

}

bool Board::AddPieces(json inJson){

    auto whiteRowConfig = inJson["default_white_config"];
    auto blackRowConfig = inJson["default_black_config"];
    int column=0;
    for (const auto& Row : whiteRowConfig) {
        int row = Row["RowNumber"];
        std::string pieceName = Row["RowElements"][column];
        std::unique_ptr<Piece> newPiece = CreatePiece(IPoint(column, row), pieceName);
        Piece* ptr = newPiece.get();
        PiecesList.push_back(ptr);

        // Add piece to the board
        Tile* tile = getTile(column, row);
        tile->setPiece(std::move(newPiece));

        column++;
    }

    for (const auto& Row : blackRowConfig) {
        int row = Row["RowNumber"];
        std::string pieceName = Row["RowElements"][column];
        std::unique_ptr<Piece> newPiece = CreatePiece(IPoint(TILE_WIDTH-column,TILE_HEIGHT-row), pieceName);
        Piece* ptr = newPiece.get();
        PiecesList.push_back(ptr);

        // Add piece to the board
        Tile* tile = getTile(column, row);
        tile->setPiece(std::move(newPiece));

        column++;
    }

    return true;
}

//Piece factory
std::unique_ptr<Piece> Board::CreatePiece(IPoint inPos, const std::string& name)
{
    if (name == "Pawn")     return std::make_unique<Piece>(inPos, PieceType::PAWN);
    if (name == "Bishop")   return std::make_unique<Piece>(inPos, PieceType::BISHOP);
    if (name == "Knight")   return std::make_unique<Piece>(inPos, PieceType::KNIGHT);
    if (name == "Tower")    return std::make_unique<Piece>(inPos, PieceType::TOWER);
    if (name == "Queen")    return std::make_unique<Piece>(inPos, PieceType::QUEEN);
    if (name == "King")     return std::make_unique<Piece>(inPos, PieceType::KING);

    return nullptr;
}


void Board::Render(Renderer& inRenderer)
{
    
    for (auto& t : TilesBoard)
    {
        t->Render(inRenderer);
    }

    for (auto& p : PiecesList)
    {
        p->Render(inRenderer);
    }

}