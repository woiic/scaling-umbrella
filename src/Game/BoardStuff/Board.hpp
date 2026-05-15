#pragma once

#include "BoardEnums.hpp"
#include "Game/CommonHeader.hpp"

#include <algorithm>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Game/GameObject.hpp"
#include "Game/TextBlock.hpp"
#include "Pieces/Piece.hpp"
#include "Tile.hpp"


class Board{
public:
    
    Board();
    ~Board();

    //-------- Core game stuff

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
    std::vector<std::unique_ptr<Piece>> TakenPiecesList;

    //-------- Rendering

    void InitPieces();
    bool AddPieces(json inJson);
    std::unique_ptr<Piece> CreatePiece(IPoint inPos, const std::string& name);

    void TestRender(Renderer& inRenderer);
    void Render(Renderer& inRenderer);

    //-------- Game handling

    void SetActivePiece(Piece* inPiece);

    void FreePieceTile(IPoint tilePos);

    void SetSourceTile(Tile* inTile);
    void SetHoverTile(Tile* inTile);

    // Moves handling

    MoveResult VerifyMove(Piece* movingPiece, IPoint finalPosition);
    MoveResult VerifySpecialMove(Piece* movingPiece, IPoint finalPosition, MoveResult expectedMoveResult);
    bool IsPointInBoard(IPoint finalPosition);

    bool MovePiece(); // intermediate point for testing
    bool TryToMovePiece(Tile* inTile);

    // extrastuff

    std::vector<Text*> textsList;
    TextBlock* testTextBlock = nullptr;

private:

// only for testing

    GameObject testGameObject = GameObject();
};