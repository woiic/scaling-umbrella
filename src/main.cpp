#include "Core/Engine.hpp"
#include "Game/Game.hpp"

int main(int argc, char* argv[]) {
    Engine engine;
    Game Game;

    if (!engine.Init("My SDL3 Engine", 800, 600)) {
        return 1;
    }

    engine.Run(Game);
    return 0;
}
