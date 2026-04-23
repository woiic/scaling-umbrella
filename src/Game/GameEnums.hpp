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
    None=0,
    PreTurn,
    White,
    Black,
    PostTurn
};