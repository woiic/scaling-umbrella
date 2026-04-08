#include "Core/Engine.hpp"
#include "Game/Game.hpp"
#include "Core/Macros.hpp"

int main(int argc, char* argv[]) {
    Engine engine;
    Game Game;

    if (!engine.Init("My SDL3 Engine", WIDTH, HEIGHT)) {
        return 1;
    }

    engine.Run(Game);
    return 0;
}
