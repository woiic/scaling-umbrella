#pragma once

#include "Core/CoreStructs.hpp"

class Board;

class Tile {

public:
    Tile();
    Tile(IPoint inPosition, Board *inBoardRef);

public:
    IPoint position;
    Board *boardRef = nullptr;

};
