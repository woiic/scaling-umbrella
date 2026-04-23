#pragma once

enum GameState
{
    None=0,
    Initializing,
    Start, // Initializing
    InGame,
    PostGame
};

enum TurnsState
{
    NONE=0,
    PreTurn,
    White,
    Black,
    PostTurn
};