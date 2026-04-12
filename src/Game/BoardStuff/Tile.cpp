#pragma once

#include "Tile.hpp"

Tile::Tile()
{
    boardRef=nullptr;
}

Tile::Tile(IPoint inPosition, Board *inBoardRef)
{
    position = inPosition;
    boardRef = inBoardRef;
}