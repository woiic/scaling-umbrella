#pragma once

#include "Core/DEBUG/Logger.hpp"
#include "Game/BoardStuff/Board.hpp"
#include "Piece.hpp"

Piece::Piece()
{
    pieceTeam = Team::NoTeam;
    position = IPoint();
    pieceType = PieceType::NoPiece;

}

Piece::Piece(IPoint inPosition, PieceType inPieceType)
{
    position = inPosition;
    pieceType = inPieceType;

}

void Piece::Update(MouseState inMouseState, float deltaTime)
{
    if (ObjectArea2D.IsMouseOver(inMouseState.mousePosition))
    {
        // Tocar/Tomar pieza (to be determined)
        if (inMouseState.bIsLeftJustPressed)
        {
            LOG_DEBUG("objecto clickeado");
            LOG_DEBUG(TeamToString(pieceTeam));
            bIsFollowingMouse = true;
            boardRef->SetActivePiece(this);
            posiblePositions = GetMovesByBehaviour();

            for (auto i : posiblePositions)
            {
                LOG_DEBUG(i.to_string());
            }
            

            return ;
        }
        if (inMouseState.bIsLeftHeld && bIsFollowingMouse)
        {
            ObjectArea2D.position = inMouseState.mousePosition;
        }
        if (inMouseState.bIsLeftJustReleased)
        {
            // moved to the board
            //MovePiece();            
        }
    }

    if (bIsFollowingMouse)
    {
        FPoint temp = (FPoint)GetSpriteWH();
        FPoint fixedPos = inMouseState.mousePosition - temp/2.0f;
        ObjectArea2D.position = fixedPos;
    }
}

void Piece::Render(Renderer& inRenderer)
{
    //GameObject::Render(inRenderer);
}


void Piece::SetPosition(IPoint inPos)
{
    position = inPos;
}


void Piece::MovePiece(bool bIsValidMovemente)
{
    if(bIsValidMovemente)
    {
        if(bIsInStartingPosition) bIsInStartingPosition = false;
        LOG_DEBUG("objecto des-clickeado");
        bIsFollowingMouse = false;
        boardRef->SetActivePiece(nullptr);

        UpdateArea2DPosition();
        return ;
    }
    bIsFollowingMouse = false;
    boardRef->SetActivePiece(nullptr);

    UpdateArea2DPosition();
    return ;
}

void Piece::FreePositionTile()
{
    boardRef->FreePieceTile(position);
}

void Piece::UpdateArea2DPosition()
{
    FPoint temp = (FPoint)GetSpriteWH();
    FPoint fixedPos = (FPoint)(position * IPoint(boardRef->TILE_WIDTH, boardRef->TILE_HEIGHT)) + temp/2.0f;
    LOG_DEBUG(fixedPos.to_string());
    ObjectArea2D.position = fixedPos;
}


std::vector<IPoint> Piece::GetMovesByBehaviour()
{
    std::vector<IPoint> points;
    switch (pieceType)
    {
    case PieceType::PAWN:
    {
        IPoint forward = IPoint(0, 1);
        
        if (pieceTeam == Team::BLACK) forward = forward * -1;
        if (boardRef->VerifyMove(this, position + forward) == MoveResult::MOVEMENT) points.push_back(position + forward);

        if (bIsInStartingPosition && boardRef->VerifyMove(this, position + 2 * forward) == MoveResult::MOVEMENT)
        {
            points.push_back(position + 2 * forward);
        }
        if (boardRef->VerifyMove(this, position + forward + IPoint(1, 0)) == MoveResult::CAPTURE) 
        {
            points.push_back(position + forward + IPoint(1, 0));
        }
        if (boardRef->VerifyMove(this, position + forward + IPoint(-1, 0)) == MoveResult::CAPTURE)
        {
            points.push_back(position + forward + IPoint(-1, 0));
        }

        // TODO: check enpassant 
        // MYB make the moving pawn notify the board-> PAWN's so they know they can do ENPASSANT and where to
        /*
        if (boardRef->VerifySpecialMove(this, position + IPoint(1, 0), MoveResult::EN_PASSANT) == MoveResult::EN_PASSANT)
        {
            points.push_back(position +IPoint(1, 0));
        }
        if (boardRef->VerifySpecialMove(this, position + IPoint(-1, 0), MoveResult::EN_PASSANT) == MoveResult::EN_PASSANT)
        {
            points.push_back(position +IPoint(-1, 0));
        }
        */
        break;
    }
    case PieceType::KNIGHT:
    {
        std::vector<IPoint> posMoves;
        posMoves.push_back(position + IPoint(1,   2));
        posMoves.push_back(position + IPoint(-1,  2));
        posMoves.push_back(position + IPoint(1,  -2));
        posMoves.push_back(position + IPoint(-1, -2));
        posMoves.push_back(position + IPoint(2,   1));
        posMoves.push_back(position + IPoint(-2,  1));
        posMoves.push_back(position + IPoint(2,  -1));
        posMoves.push_back(position + IPoint(-2, -1));
        for (auto p : posMoves)
        {
            if (boardRef->VerifyMove(this, p) != MoveResult::NON_POSSIBLE)
            {
                points.push_back(p);
            }
        }
        break;
    }
    case PieceType::BISHOP:
    {

        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(1 ,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 ,  1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(1 , -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 , -1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(-1,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1,  1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(-1, -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1, -1));
            else break;
        }
        break;
    }
    case PieceType::ROOK:
    {
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(1 ,  0)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 ,  0));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(0 ,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(0 ,  1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(-1,  0)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1,  0));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(0 , -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(0 , -1));
            else break;
        }
        break;
    }
    case PieceType::QUEEN:
    {
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(1 ,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 ,  1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(1 , -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 , -1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(-1,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1,  1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(-1, -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1, -1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(1 ,  0)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 ,  0));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(0 ,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(0 ,  1));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(-1,  0)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1,  0));
            else break;
        }
        for (int i=1; i<(__max(boardRef->boardWidth, boardRef->boardHeight) - 1); i++)
        {
            if (boardRef->VerifyMove(this, position + i * IPoint(0 , -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(0 , -1));
            else break;
        }
        break;
    }
    case PieceType::KING:
    {
        if (boardRef->VerifyMove(this, position + IPoint(1 ,  0)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 ,  0));
        if (boardRef->VerifyMove(this, position + IPoint(1 ,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 ,  1));
        
        if (boardRef->VerifyMove(this, position + IPoint(0 ,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(0 ,  1));
        if (boardRef->VerifyMove(this, position + IPoint(-1,  1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1,  1));
        
        if (boardRef->VerifyMove(this, position + IPoint(-1,  0)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1,  0));
        if (boardRef->VerifyMove(this, position + IPoint(-1, -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(-1, -1));
        
        if (boardRef->VerifyMove(this, position + IPoint(0 , -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(0 , -1));
        if (boardRef->VerifyMove(this, position + IPoint(1 , -1)) != MoveResult::NON_POSSIBLE) points.push_back(position + IPoint(1 , -1));        

        break;
    }

    default:
        break;
    }
    return points;
}
