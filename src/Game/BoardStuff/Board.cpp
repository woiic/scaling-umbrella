#pragma once

#include "Core/Graphic/TextureManager.hpp"
#include "Board.hpp"

Board::Board()
{
    
}

void Board::Update(MouseState inMouseState, float deltaTime)
{
    for (auto& t : TilesBoard)
    {
        if(t)
        {
            t->Update(inMouseState, deltaTime);
        }
    }

    for (auto& p : PiecesList)
    {
        if (p) 
        {
            p->Update(inMouseState, deltaTime);
        }
    }
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

    boardWidth = inBoardWidth;
    boardHeight = inBoardHeight;
    
    for(int i=0; i<inBoardHeight; i++)
    {
        for(int j=0; j<inBoardWidth; j++)
        {
            //Tile newTile = Tile(FPoint(i, j), this);
            std::unique_ptr<Tile> ptr = std::make_unique<Tile>(IPoint(i, j), this);

            Color c;
            if ((i+j)%2 == 0) ptr->ObjectSprite = TextureManager::Get("assets/Sprites/white_tile.png");
            else ptr->ObjectSprite = TextureManager::Get("assets/Sprites/black_tile.png");
            Area2D tempArea2D = Area2D(FPoint((float)(j*TILE_WIDTH), (float)(i*TILE_HEIGHT)),
                                        (float)TILE_WIDTH,
                                        (float)TILE_HEIGHT,
                                        c);
            ptr->setArea2D(tempArea2D);

            TilesBoard.push_back(std::move(ptr));
        }   
    }
    
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
    int column = 0;
    for (const auto& Row : whiteRowConfig) {
        int row = Row["RowNumber"];
        column = 0;
        for (const auto& piece : Row["RowElements"]) 
        {
            std::string pieceName = piece.get<std::string>();
            std::unique_ptr<Piece> newPiece = CreatePiece(IPoint(column, row), pieceName);
            //newPiece->ObjectSprite = TextureManager::Get("assets/Sprites/black_tile.png");
            if (!newPiece) {
                std::cout << "Piece problem" << std::endl;
                column++;
                continue;
            }
            std::transform(pieceName.begin(), pieceName.end(), pieceName.begin(),
                [](unsigned char c){ return std::tolower(c); });

            LOG_DEBUG(pieceName);
            newPiece->ObjectSprite = TextureManager::Get("assets/Sprites/white_" + pieceName + ".png" );
            newPiece->pieceTeam = Team::WHITE;
            Color c = Color();
            FPoint piecePos = FPoint((float)(column*TILE_WIDTH + (TILE_WIDTH - newPiece->GetSpriteWH().x)/2.0f),
                                     (float)(row*TILE_HEIGHT + (TILE_HEIGHT - newPiece->GetSpriteWH().y)/2.0f));
            Area2D tempArea2D = Area2D(piecePos,
                                        (float)TILE_WIDTH,
                                        (float)TILE_HEIGHT,
                                        c);
            newPiece->setArea2D(tempArea2D);
            
            Piece* ptr = newPiece.get();
            // Add piece to the board
            Tile* tile = getTile(row, column);
            if (!tile) {
                std::cout << "Tile problem" << std::endl;
                column++;
                continue;
            }
            tile->setPiece(ptr);
            
            PiecesList.push_back(std::move(newPiece));
            column++;
        }
    }

    for (const auto& Row : blackRowConfig) {
        int row = (boardHeight - 1) - static_cast<int>(Row["RowNumber"]);
        column = 0;
        for (const auto& piece : Row["RowElements"]) 
        {
            std::string pieceName = piece.get<std::string>();
            std::unique_ptr<Piece> newPiece = CreatePiece(IPoint(column, row), pieceName);

            if (!newPiece) {
                std::cout << "Piece problem" << std::endl;
                column++;
                continue;
            }

            std::transform(pieceName.begin(), pieceName.end(), pieceName.begin(),
                [](unsigned char c){ return std::tolower(c); });
            newPiece->ObjectSprite = TextureManager::Get("assets/Sprites/black_" + pieceName + ".png" );
            newPiece->pieceTeam = Team::BLACK;
            Color c = Color();
            FPoint piecePos = FPoint((float)(column*TILE_WIDTH + (TILE_WIDTH - newPiece->GetSpriteWH().x)/2.0f),
                                     (float)(row*TILE_HEIGHT + (TILE_HEIGHT - newPiece->GetSpriteWH().y)/2.0f));
            Area2D tempArea2D = Area2D(piecePos,
                                        (float)TILE_WIDTH,
                                        (float)TILE_HEIGHT,
                                        c);
            newPiece->setArea2D(tempArea2D);

            Piece* ptr = newPiece.get();
            // Add piece to the board
            Tile* tile = getTile(row, column);
            if (!tile) {
                std::cout << "Tile problem" << std::endl;
                column++;
                continue;
            }
            tile->setPiece(ptr);

            PiecesList.push_back(std::move(newPiece));
            column++;
        }
    }

    return true;
}

//Piece factory
std::unique_ptr<Piece> Board::CreatePiece(IPoint inPos, const std::string& name)
{
    if (name == "Pawn")     return std::make_unique<Piece>(inPos, PieceType::PAWN);
    if (name == "Bishop")   return std::make_unique<Piece>(inPos, PieceType::BISHOP);
    if (name == "Knight")   return std::make_unique<Piece>(inPos, PieceType::KNIGHT);
    if (name == "ROOK")    return std::make_unique<Piece>(inPos, PieceType::ROOK);
    if (name == "Queen")    return std::make_unique<Piece>(inPos, PieceType::QUEEN);
    if (name == "King")     return std::make_unique<Piece>(inPos, PieceType::KING);

    return nullptr;
}

void Board::TestRender(Renderer& inRenderer)
{
    testGameObject.RenderSprite(inRenderer);
}

void Board::Render(Renderer& inRenderer)
{
    
    for (auto& t : TilesBoard)
    {
        //t->Render(inRenderer);
        t->RenderSprite(inRenderer);
    }

    for (auto& p : PiecesList)
    {
        if (p) 
        {
            //p->Render(inRenderer);
            p->RenderSprite(inRenderer);
        }
    }
    
    return ;
}