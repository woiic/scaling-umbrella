#include "Core/Engine.hpp"

int main(int argc, char* argv[]) {
    Engine engine;

    if (!engine.Init("My SDL3 Engine", 800, 600)) {
        return 1;
    }

    engine.Run();
    return 0;
}
