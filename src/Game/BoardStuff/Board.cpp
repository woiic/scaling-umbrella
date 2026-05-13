#pragma once

#include "Core/Graphic/TextureManager.hpp"
#include "Core/Graphic/Text.hpp"
#include "Board.hpp"

Board::Board()
{
    
}

Board::~Board()
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

    // check for checks

    // check if End Game has been reached

    // change player controller

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
            std::unique_ptr<Tile> ptr = std::make_unique<Tile>(IPoint(j, i), this);

            Color c;
            if ((i+j)%2 == 0) ptr->ObjectSprite = TextureManager::GetSprite("assets/Sprites/white_tile.png");
            else ptr->ObjectSprite = TextureManager::GetSprite("assets/Sprites/black_tile.png");
            Area2D tempArea2D = Area2D(FPoint((float)(j*TILE_WIDTH), (float)(i*TILE_HEIGHT)),
                                        (float)TILE_WIDTH,
                                        (float)TILE_HEIGHT,
                                        c);
            ptr->setArea2D(tempArea2D);
            TilesBoard.push_back(std::move(ptr));
        }   
    }

    // Show some text
    if (true)
    {
        Text* txt = TextureManager::GetText("test");
        testTextBlock = new TextBlock();
        testTextBlock->SetText(txt);
        Area2D tArea = Area2D(FPoint(8*TILE_WIDTH + 12.0f, 12.0f), 100, 50, Color());
        testTextBlock->setArea2D(tArea);
        textsList.push_back(txt);
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
            
            // ensure piece knows its board so callbacks or queries are safe
            if (newPiece) newPiece->boardRef = this;
            
            if (!newPiece) {
                std::cout << "Piece problem" << std::endl;
                column++;
                continue;
            }
            std::transform(pieceName.begin(), pieceName.end(), pieceName.begin(),
                [](unsigned char c){ return std::tolower(c); });

            LOG_DEBUG(pieceName);
            newPiece->ObjectSprite = TextureManager::GetSprite("assets/Sprites/white_" + pieceName + ".png" );
            newPiece->pieceTeam = Team::WHITE;
            Color c = Color();
            FPoint piecePos = FPoint((float)(column*TILE_WIDTH + (TILE_WIDTH - newPiece->GetSpriteWH().x)/2.0f),
                                     (float)(row*TILE_HEIGHT + (TILE_HEIGHT - newPiece->GetSpriteWH().y)/2.0f));
            Area2D tempArea2D = Area2D(piecePos,
                                        (float)TILE_WIDTH,
                                        (float)TILE_HEIGHT,
                                        c);
            newPiece->setArea2D(tempArea2D);
            newPiece->position = IPoint(column, row);

            Piece* ptr = newPiece.get();
            // Add piece to the board
            Tile* tile = getTile(column, row);
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
            // ensure piece knows its board so callbacks or queries are safe
            if (newPiece) newPiece->boardRef = this;

            if (!newPiece) {
                std::cout << "Piece problem" << std::endl;
                column++;
                continue;
            }

            std::transform(pieceName.begin(), pieceName.end(), pieceName.begin(),
                [](unsigned char c){ return std::tolower(c); });
            newPiece->ObjectSprite = TextureManager::GetSprite("assets/Sprites/black_" + pieceName + ".png" );
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
            Tile* tile = getTile(column, row);
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

    // for testing
    if(testTextBlock) testTextBlock->RenderText(inRenderer);
    
    return ;
}

Tile* Board::getTile(int i, int j)
{
    if(i < 0 || j < 0 ) return nullptr;
    if(i + j * boardWidth < TilesBoard.size())
    {
        return TilesBoard[i + j * boardWidth].get();
    }
    return nullptr;
    }
    
Tile* Board::getTile(IPoint inPos)
{
    if(inPos.x < 0 || inPos.y < 0 ) return nullptr;
    if(inPos.x + inPos.y * boardWidth < TilesBoard.size())
    {
        return TilesBoard[inPos.x + inPos.y * boardWidth].get();
    }
    return nullptr;
}

void Board::SetActivePiece(Piece* inPiece)
{
    activePiece = inPiece;
}

void Board::FreePieceTile(IPoint tilePos)
{
    LOG_DEBUG("Tile liberado" + tilePos.to_string());
    getTile(tilePos)->AssignedPiece = nullptr;
}

void Board::SetSourceTile(Tile* inTile)
{
    sourceTile = inTile;
}

void Board::SetHoverTile(Tile* inTile)
{
    hoverTile = inTile;
}

MoveResult Board::VerifyMove(Piece* movingPiece, IPoint finalPosition)
{
    if (!IsPointInBoard(finalPosition))
    {
        return MoveResult::NON_POSSIBLE;    
    }
    if (getTile(finalPosition)->AssignedPiece)
    {
        Piece* tempPiece = getTile(finalPosition)->AssignedPiece;
        if (tempPiece)
        {
            if (tempPiece->pieceTeam == movingPiece->pieceTeam) return MoveResult::NON_POSSIBLE;
            else return MoveResult::CAPTURE;
        }
        return MoveResult::MOVEMENT;    
    }

    return MoveResult::MOVEMENT;
}
//TODO: CHECK EN PASSANT (probably an improved move system IPoint -> Moves )
MoveResult Board::VerifySpecialMove(Piece* movingPiece, IPoint finalPosition, MoveResult expectedMoveResult)
{
    if (!IsPointInBoard(finalPosition))
    {
        return MoveResult::NON_POSSIBLE;    
    }
    if (getTile(finalPosition)->AssignedPiece)
    {
        // EN PASSANT
        Piece* tempPiece = getTile(finalPosition)->AssignedPiece;
        if (movingPiece->pieceType == PieceType::PAWN)
        {
            if (tempPiece && tempPiece->pieceType == PieceType::PAWN)
            {
                if (tempPiece->pieceTeam == movingPiece->pieceTeam && tempPiece->bHasMoved2Tiles) // has made a 2 tiles move
                {
                    //
                }
            }
        }
        if (tempPiece)
        {
            if (tempPiece->pieceTeam == movingPiece->pieceTeam) return MoveResult::NON_POSSIBLE;
            else return MoveResult::CAPTURE;
        }
        return MoveResult::MOVEMENT;    
    }

    return MoveResult::MOVEMENT;
}

bool Board::IsPointInBoard(IPoint finalPosition)
{
    if (boardWidth > finalPosition.x && boardHeight > finalPosition.y)
    {
        if (finalPosition.x >= 0 && finalPosition.y >= 0)
        {
            return true;
        }
    }
    return false;
}

bool Board::MovePiece()
{
    return TryToMovePiece(hoverTile);
}

bool Board::TryToMovePiece(Tile* inTile)
{
    if (!activePiece || !inTile) return false;
    if (activePiece->posiblePositions.empty()) return false;
    if (! hoverTile) return false;

    const auto& vec = activePiece->posiblePositions;
    if (std::find(vec.begin(), vec.end(), inTile->position) == vec.end()) 
    {

        activePiece->MovePiece(false); // return piece to "spawn"
        return false;
    }

    // Check for a piece to be taken - Pieces of the same Team are ignored on the GetMovesPart()

    //

    LOG_DEBUG("Tile a modificar");
    LOG_DEBUG(inTile->position.to_string());
    FreePieceTile(activePiece->position); // Removes the pointer from Tile 1
    LOG_DEBUG("Tile liberado");
    activePiece->SetPosition(inTile->position); // Sets Piece new position
    LOG_DEBUG("Piece Tile changed");
    inTile->AssignedPiece = activePiece; //assigns the Piece to Tile 2
    LOG_DEBUG("Piece Tile setted");

    activePiece->MovePiece(true); // Sets the "world" position to the center of the Tile

    return true;
    
}