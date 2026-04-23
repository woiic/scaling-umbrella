#pragma once

#include "Game/CommonHeader.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Pieces/Piece.hpp"
#include "Tile.hpp"


class Board{
public:
    
    Board();

    void Update(MouseState inMouseState, float deltaTime);
    std::vector<std::unique_ptr<Tile>> TilesBoard;
    
    int TILE_WIDTH = 65;//65;
    int TILE_HEIGHT = 65;//65;

    int boardWidth;
    int boardHeight;
    void InitBoard(int inBoardWidth, int inBoardHeight, int inTileWidth, int inTileHeight);

    Tile* getTile(int i, int j){
        if(i < 0 || j < 0 ) return nullptr;
        if(i * boardWidth + j < TilesBoard.size())
        {
            return TilesBoard[i * boardWidth + j].get();
        }
        return nullptr;
    }
    
    std::vector<std::unique_ptr<Piece>> PiecesList;


    void InitPieces();
    bool AddPieces(json inJson);
    std::unique_ptr<Piece> CreatePiece(IPoint inPos, const std::string& name);

    void TestRender(Renderer& inRenderer);
    void Render(Renderer& inRenderer);

private:

// only for testing

    GameObject testGameObject = GameObject();
};