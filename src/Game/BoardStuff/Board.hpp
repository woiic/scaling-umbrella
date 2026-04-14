#pragma once

#include "Game/CommonHeader.hpp"
//#include "Game/GameObject.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Pieces/Piece.hpp"
#include "Tile.hpp"


class Board{
public:
    
    Board();
    std::vector<std::unique_ptr<Tile>> TilesBoard;
    
    int boardWidth;
    int boardHeight;
    void InitBoard(int inBoardWidth, int inBoardHeight);

    Tile* getTile(int i, int j){
        return TilesBoard[i * boardWidth + j].get();
    }
    
    std::vector<Piece*> PiecesList;


    void InitPieces();
    bool AddPieces(json inJson);
    std::unique_ptr<Piece> CreatePiece(IPoint inPos, const std::string& name);


    void Render(Renderer& inRenderer);
private:



};