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
    Piece* activePiece = nullptr;
    Tile* sourceTile = nullptr;
    Tile* hoverTile = nullptr;

    int TILE_WIDTH = 65;//65;
    int TILE_HEIGHT = 65;//65;

    int boardWidth;
    int boardHeight;
    void InitBoard(int inBoardWidth, int inBoardHeight, int inTileWidth, int inTileHeight);

    Tile* getTile(int i, int j);
    
    Tile* getTile(IPoint inPos);

    std::vector<std::unique_ptr<Piece>> PiecesList;

    // Rendering

    void InitPieces();
    bool AddPieces(json inJson);
    std::unique_ptr<Piece> CreatePiece(IPoint inPos, const std::string& name);

    void TestRender(Renderer& inRenderer);
    void Render(Renderer& inRenderer);

    // Game handling

    void SetActivePiece(Piece* inPiece);

    void FreePieceTile(IPoint tilePos);

    void SetSourceTile(Tile* inTile);
    void SetHoverTile(Tile* inTile);

private:

// only for testing

    GameObject testGameObject = GameObject();
};