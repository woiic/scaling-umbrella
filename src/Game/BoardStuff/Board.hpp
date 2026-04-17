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
    
    int TILE_WIDTH = 16;
    int TILE_HEIGHT = 16;

    int boardWidth;
    int boardHeight;
    void InitBoard(int inBoardWidth, int inBoardHeight, int inTileWidth, int inTileHeight);

    Tile* getTile(int i, int j){
        return TilesBoard[i * boardWidth + j].get();
    }
    
    std::vector<Piece*> PiecesList;


    void InitPieces();
    bool AddPieces(json inJson);
    std::unique_ptr<Piece> CreatePiece(IPoint inPos, const std::string& name);

    void TestRender(Renderer& inRenderer);
    void Render(Renderer& inRenderer);

private:

// only for testing

    GameObject testGameObject = GameObject();
};